from __future__ import annotations
import sys
from typing import Dict, List

from copy import deepcopy
import saport.simplex.model as ssmod
import saport.simplex.expressions.objective as sseobj
import saport.simplex.expressions.constraint as ssecon
import saport.simplex.expressions.expression as sseexp
import saport.simplex.solution as sssol
import saport.simplex.tableaux as sstab
import numpy as np

class Solver:
    """
        A class to represent a simplex solver.

        Attributes:
        ______
        _slacks: Dict[Variable, Constraint]:
            contains mapping from slack variables to their corresponding constraints
        _surpluses: Dict[Variable, Constraint]:
            contains mapping from surplus variables to their corresponding constraints
        _artificial: Dict[Variable, Constraint]:
            contains mapping from artificial variables to their corresponding constraints

        Methods
        -------
        solve(model: Model) -> Tableaux:
            solves the given model and return the first solution
    """
    _slacks: Dict[sseexp.Variable, ssecon.Constraint]
    _surpluses: Dict[sseexp.Variable, ssecon.Constraint]
    _artificial: Dict[sseexp.Variable, ssecon.Constraint]

    def solve(self, model: ssmod.Model):
        normal_model = self._augment_model(model)
        if len(self._slacks) < len(normal_model.constraints):
            tableaux, success = self._presolve(normal_model)
            if not success:
                return sssol.Solution.infeasible(model, tableaux, tableaux)
        else:
            tableaux = self._basic_initial_tableaux(normal_model)

        initial_tableaux = deepcopy(tableaux)
        if self._optimize(tableaux) == False:
            return sssol.Solution.unbounded(model, initial_tableaux, tableaux)

        assignment = tableaux.extract_assignment()
        return self._create_solution(assignment, model, initial_tableaux, tableaux)

    def _optimize(self, tableaux: sstab.Tableaux):
        while not tableaux.is_optimal():
            pivot_col = tableaux.choose_entering_variable()
            if tableaux.is_unbounded(pivot_col):
                return False
            pivot_row = tableaux.choose_leaving_variable(pivot_col)

            tableaux.pivot(pivot_row, pivot_col)
        return True

    def _presolve(self, model: ssmod.Model):
        """
            _presolve(model: Model) -> Tableaux:
                returns a initial tableaux for the second phase of simplex
        """
        presolve_model = self._create_presolve_model(model)
        tableaux = self._presolve_initial_tableaux(presolve_model)

        self._optimize(tableaux)

        if self._artifical_variables_are_positive(tableaux):
            return (tableaux, False)

        tableaux = self._restore_initial_tableaux(tableaux, model)
        return (tableaux, True)

    def _augment_model(self, original_model: ssmod.Model):
        """
            _augment_model(model: Model) -> Model:
                returns an augmented version of the given model
        """
        model = deepcopy(original_model)
        model.simplify()
        self._change_objective_to_max(model)
        self._change_constraints_bounds_to_nonnegative(model)
        self._slacks = self._add_slack_variables(model)
        self._surpluses = self._add_surplus_variables(model)
        return model

    def _create_presolve_model(self, augmented_model: ssmod.Model):
        presolve_model = deepcopy(augmented_model)
        self._artificial = self._add_artificial_variables(presolve_model)
        return presolve_model

    def _change_objective_to_max(self, model: ssmod.Model):
        if model.objective.type == sseobj.ObjectiveType.MIN:
            model.objective.invert()


    def _change_constraints_bounds_to_nonnegative(self, model: ssmod.Model):
        for constraint in model.constraints:
            if constraint.bound < 0:
                constraint.invert()

    def _add_slack_variables(self, model: ssmod.Model) -> List[sseexp.Variable]:
        slacks: Dict[sseexp.Variable, ssecon.Constraint] = dict()

        for constraint in model.constraints:
            if constraint.type == ssecon.ConstraintType.LE:
                slack_var = model.create_variable(f"s{constraint.index}")
                slacks[slack_var] = constraint
                constraint.expression = constraint.expression + slack_var
                constraint.type = ssecon.ConstraintType.EQ
        return slacks

    def _add_surplus_variables(self, model: ssmod.Model) -> List[sseexp.Variable]:
        surpluses: Dict[sseexp.Variable, ssecon.Constraint] = dict()
        for constraint in model.constraints:
            if constraint.type == ssecon.ConstraintType.GE:
                surplus_var = model.create_variable(f"s{constraint.index}")
                surpluses[surplus_var] = constraint
                constraint.expression = constraint.expression - surplus_var
                constraint.type = ssecon.ConstraintType.EQ
        return surpluses

    def _add_artificial_variables(self, model: ssmod.Model):
        artificial_variables: Dict[sseexp.Variable, ssecon.Constraint] = dict()
        for constraint in model.constraints.copy():
            if len([c for c in self._slacks.values() if c.index == constraint.index]) > 0:
                continue
            artificial_var = model.create_variable(f"R{constraint.index}")
            artificial_variables[artificial_var] = constraint
            constraint.expression = constraint.expression + artificial_var
        return artificial_variables

    def _presolve_initial_tableaux(self, model: ssmod.Model):
        objective_row = np.array([0.0 for _ in model.variables] + [0.0])

        for var in self._artificial.keys():
            objective_row[var.index] = 1.0

        table = np.array([objective_row] + [c.expression.coefficients(model) + [c.bound] for c in model.constraints])

        for c in self._artificial.values():
            constraint = model.constraints[c.index]
            factors_row = np.array(constraint.expression.coefficients(model) + [constraint.bound])
            objective_row = objective_row - factors_row

        table = np.array([objective_row] + [c.expression.coefficients(model) + [c.bound] for c in model.constraints])
        return sstab.Tableaux(model, table)

    def _basic_initial_tableaux(self, model: ssmod.Model):
        objective_row = np.array((-1 * model.objective.expression).coefficients(model) + [0.0])
        table = np.array([objective_row] + [c.expression.coefficients(model) + [c.bound] for c in model.constraints])
        return sstab.Tableaux(model, table)

    def _artifical_variables_are_positive(self, tableaux: sstab.Tableaux):
        assignment = tableaux.extract_assignment()
        for artificial_var in self._artificial:
            if assignment[artificial_var.index] > 0:
                return True
        return False

    def _restore_initial_tableaux(self, tableaux, model):
        basis = tableaux.extract_basis()
        tableaux = self._remove_artificial_variables(tableaux)
        tableaux = self._restore_original_objective_row(tableaux, model)
        tableaux = self._fix_objective_row_to_the_basis(tableaux, basis)
        return tableaux

    def _remove_artificial_variables(self, tableaux: sstab.Tableaux):
        columns_to_remove = [var.index for var in self._artificial.keys()]
        table = np.delete(tableaux.table, columns_to_remove, 1)
        return sstab.Tableaux(tableaux.model, table)

    def _restore_original_objective_row(self, tableaux: sstab.Tableaux, model: ssmod.Model):
        objective_row = np.array((-1 * model.objective.expression).coefficients(model) + [0.0])
        new_table = np.array(tableaux.table)
        new_table[0] = objective_row
        return sstab.Tableaux(model, new_table)

    def _fix_objective_row_to_the_basis(self, tableaux: sstab.Tableaux, basis: List[int]):
        objective_row = tableaux.table[0].copy()

        for (constr_index, col) in enumerate(basis):
            if col >= len(objective_row) - 1:
                continue

            row = constr_index + 1
            objective_factor = objective_row[col]
            if objective_factor == 0:
                continue
            objective_row = objective_row - objective_factor * tableaux.table[row]

        new_table = np.array(tableaux.table)
        new_table[0] = objective_row
        return sstab.Tableaux(tableaux.model, new_table)

    def _create_solution(self, assignment: List[float], model: ssmod.Model, initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
        return sssol.Solution.with_assignment(model, assignment, initial_tableaux, tableaux)