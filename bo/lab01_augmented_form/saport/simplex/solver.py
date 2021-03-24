from __future__ import annotations
from typing import Dict, List

from copy import deepcopy
from . import model as ssmod
from .expressions import constraint as ssecon
from .expressions import expression as sseexp
from .expressions import objective as sseobj
from . import solution as sssol
from . import tableaux as sstab
import numpy as np


class Solver:
    """
        A class to represent a simplex solver.

        Methods
        -------
        solve(model: Model) -> Tableaux:
            solves the given model and return the first solution
    """

    def solve(self, model: ssmod.Model) -> sssol.Solution:
        augmented_model = self._augment_model(model)
        tableaux = self._basic_initial_tableaux(augmented_model)
        solution = self._extract_solution(tableaux, model)
        return solution

    def _augment_model(self, original_model: ssmod.Model) -> ssmod.Model:
        """
            _augment_model(model: Model) -> Model:
                returns an augmented version of the given model 
        """
        # We don't want to modify the original model
        model = deepcopy(original_model)
        # Wa want to have simplified expressions 
        # (each variable) should occur only once in every expression
        model.simplify()

        if model.objective.type == sseobj.ObjectiveType.MIN:
            model.objective.invert()

        for constraint in model.constraints:
            if constraint.bound < 0:
                constraint.invert()
            if constraint.type == ssecon.ConstraintType.LE:
                constraint.expression += model.create_variable(f"s{constraint.index + 1}")
            if constraint.type == ssecon.ConstraintType.GE:
                constraint.expression -= model.create_variable(f"s{constraint.index + 1}")
            constraint.type = ssecon.ConstraintType.EQ

        return model

    def _basic_initial_tableaux(self, model: ssmod.Model) -> sstab.Tableaux:
        # TODO:
        # replace the 'None' below with a numpy array, where
        # 1) first row consists of the inverted coefficients of the objective expression 
        #    plus 0.0 in the last column
        # 2) every other row consists of the coefficitients in the corresponding constraints, 
        #    don't forget to put the constraint bound in the last column
        # tips.
        # - to invert coefficients in the expression, one can multiply it by "-1"
        # - to get coefficients one can use the coefficients method in the expression object

        tmp = model.objective.expression.coefficients(model)
        tmp.append(0)
        tmp = [-1 * el for el in tmp]
        table = np.array(tmp)
        for constraint in model.constraints:
            _tmpList = constraint.expression.coefficients(model)
            _tmpList.append(constraint.bound)
            table = np.vstack([table, np.array(_tmpList)])

        return sstab.Tableaux(model, table)

    def _extract_solution(self, tableaux: sstab.Tableaux, model: ssmod.Model) -> sssol.Solution:
        return sssol.Solution(model, tableaux)
