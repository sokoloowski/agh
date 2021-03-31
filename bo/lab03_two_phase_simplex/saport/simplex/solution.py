from __future__ import annotations
from typing import List

import saport.simplex.model as ssmod
import saport.simplex.tableaux as sstab
import saport.simplex.expressions.expression as sseexp

class Solution:
    """
        A class to represent a solution to linear programming problem.


        Attributes
        ----------
        model : Model
            model corresponding to the solution
        initial_tableaux: Tableaux
            a simplex tableaux corresponding to the first base solution
        tableaux: Tableaux
            a simplex tableaux corresponding to the solution 
        is_feasible: bool
            whether the problem is feasible
        is_bounded: bool
            whether the problem is bounded

        Methods
        -------
        __init__(model: Model, assignment: list[float] | None, initial_tableaux: Tableaux, tableaux: Tableaux, is_feasible: bool, is_bounded: bool) -> Solution:
            constructs a new solution for the specified model, assignment, tableaux
            if the assignment is null, one of the flags should false - either the solution is infeasible or is unbounded
        assignment(model: Model | None) -> List[float]:
            list with the values assigned to the variables in the model if solution is feasible and bounded, otherwise None
            order of values should correspond to the order of variables in model.variables list
            if model is None, method defaults to the model attribute
        value(var: Variable) -> float | None:
            returns a value assigned to the specified variable if the model is feasible and bounded, otherwise None
        objective_value() -> float | None:
            returns a value of the objective function if the model is feasible and bounded, otherwise None
        has_assignment() -> bool:
            helper method returning info if the model is feasible and bounded, only then there is an assignment available
    
        Static Methods
        --------------
        with_assignment(model: ssmod.Model, assignment: List[float], initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
            helper method to creata solutions with valid assignments
        infeasible(model: ssmod.Model, initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):    
            helper method to create infeasible solutions
        unbounded(model, initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
            helper method to create unbounded solutions
    """

    def __init__(self, model: ssmod.Model, assignment: List[float], initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux, is_feasible: bool, is_bounded: bool):
        self.model = model 
        self.is_feasible = is_feasible
        self.is_bounded = is_bounded
        self.tableaux = tableaux
        self.initial_tableaux = initial_tableaux
        self._assignment = assignment

    def assignment(self, model: ssmod.Model = None):
        model = self.model if model is None else model
        return self._assignment[:len(model.variables)]

    def value(self, var: sseexp.Variable):
        return None if self._assignment == None else self._assignment[var.index]

    def objective_value(self):
        return None if self._assignment == None else self.model.objective.evaluate(self._assignment) 

    def has_assignment(self):
        return self._assignment == None

    @staticmethod
    def with_assignment(model: ssmod.Model, assignment: List[float], initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
        return Solution(model, assignment, initial_tableaux, tableaux, True, True)  

    @staticmethod
    def infeasible(model: ssmod.Model, initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
        return Solution(model, None, initial_tableaux, tableaux, False, True)   

    @staticmethod
    def unbounded(model, initial_tableaux: sstab.Tableaux, tableaux: sstab.Tableaux):
        return Solution(model, None, initial_tableaux, tableaux, True, False)

    def __str__(self, model: ssmod.Model = None):
        model = self.model if model is None else model
        
        if not self.is_bounded:
            return "There is no optimal solution, the model is unbounded"

        if not self.is_feasible:
            return "There is no optimal solution, the model is infeasible"
            
        text = f'- objective value: {self.objective_value()}\n'
        text += '- assignment:'
        for var in model.variables:
            text += f'\n\t- {var.name} = {"{:.3f}".format(self._assignment[var.index])}'
        return text