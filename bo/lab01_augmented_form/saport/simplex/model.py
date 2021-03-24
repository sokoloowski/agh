from __future__ import annotations
from typing import List

import saport.simplex.expressions.objective as sseobj
import saport.simplex.expressions.constraint as ssecon
import saport.simplex.solver as ssslv
import saport.simplex.expressions.expression as sseexp
import saport.simplex.solution as sssol
from copy import deepcopy

class Model:
    """
        A class to represent a linear programming problem.

        Attributes
        ----------
        name : str
            name of the problem
        variables : list[Variable]
            list with the problem variable, variable with index 'i' is always stored at the variables[i]
        constraints : list[Constraint]
            list containing problem constraints
        objective : Objective
            object representing the objective function

        Methods
        -------
        __init__(name: str):
            constructs new model with a specified name
        create_variable(name: str) -> Variable
            returns a new variable with a specified named, the variable is automatically indexed and added to the variables list
        add_constraint(constraint: Constraint)
            add a new constraint to the model
        maximize(expression: Expression)
            sets objective to maximize the specified Expression
        minimize(expression: Expression)
            sets objective to minimize the specified Expression
        simplify():
            simplifies all the expressions used in the model
        solve() -> Solution
            solves the current model using Simplex solver and returns the result
            when called, the model should already contain at least one variable and objective
    """
    name: str
    variables: List[sseexp.Variable]
    constraints: List[ssecon.Constraint]
    objective: sseobj.Objective
    
    def __init__(self, name: str):
        self.name = name
        self.variables = []
        self.constraints = []
        self.objective = None

    def create_variable(self, name: str) -> sseexp.Variable:
        for var in self.variables:
            if (var.name == name):
                raise Exception(f"There is already a variable named {name}")

        new_index = len(self.variables)
        variable = sseexp.Variable(name, new_index)
        self.variables.append(variable)
        return variable 

    def add_constraint(self, constraint: ssecon.Constraint):
        constraint.index = len(self.constraints)
        self.constraints.append(constraint)
         
    def maximize(self, expression: sseexp.Expression):
        self.objective = sseobj.Objective(expression, sseobj.ObjectiveType.MAX)
    
    def minimize(self, expression):
        self.objective = sseobj.Objective(expression, sseobj.ObjectiveType.MIN)
        
    def simplify(self):
        """ Simplifies all expressions in the model """
        for c in self.constraints:
            c.simplify()
        self.objective.simplify()

    def solve(self) -> sssol.Solution:
        if len(self.variables) == 0:
            raise Exception("Can't solve a model without any variables")

        if self.objective == None:
            raise Exception("Can't solve a model without an objective")

        solver = ssslv.Solver()
        return solver.solve(self)

    def __str__(self) -> str:
        separator = '\n\t'
        text = f'''- name: {self.name}
- variables:{separator}{separator.join([f"{v.name} >= 0" for v in self.variables])}
- constraints:{separator}{separator.join([str(c) for c in self.constraints])}
- objective:{separator}{self.objective}
'''
        return text
        