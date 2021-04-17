from __future__ import annotations
from enum import Enum
from typing import List
import saport.simplex.expressions.expression as sseexp
import saport.simplex.model as ssmod

class ObjectiveType(Enum):
    """
        An enum to represent an objective type:
        - MAX = maximize the objective
        - MIN = minimze the objective
    """
    MAX = 1
    MIN = -1

    def __str__(self) -> str:
        return {
            ObjectiveType.MAX: 'max',
            ObjectiveType.MIN: 'min'
        }[self]

class Objective: 
    """
        A class to represent an objective in the linear programming expression, e.g. 4x + 5y -> max, etc.

        Attributes
        ----------
        expression : Expression
            polynomial expressions that is being optimized
        type: ObjectiveType
            type of the objective: MIN, MAX
        coefficient: float
            coefficient associated with the objective variable used in simplex algorithm

        Methods
        -------
        __init__(expression: Expression, type: ObjectiveType = ObjectiveType.Max) -> Constraint:
            constructs new objective with a specified polynomial and type
        simplified() -> Objective:
            returns new objective with the simplified polynomial
        invert():
            inverts objective, keeping the "objective variable factor" intact  
        evaluate(assignemnt: list[float]) -> float:
            returns value of the objective for the given assignment
            assignment is just a list of floats corresponding (by index) to the variables in the model 
        is_equivalent(other: Objective, model: Model) -> bool:
            returns true if other objective is equivalent given the specific model
    """
    expression: sseexp.Expression
    type: ObjectiveType
    coefficient: float

    def __init__(self, expression: sseexp.Expression, type: ObjectiveType = ObjectiveType.MAX, factor: float = 1.0):
        self.expression = expression
        self.type = type
        self.coefficient = factor

    def invert(self):
        self.expression = self.expression * -1
        self.type = ObjectiveType(self.type.value * -1)
        self.coefficient = self.coefficient * -1

    def simplify(self):
        self.expression.simplify()

    def depends_on_variable(self, model: ssmod.Model, variable: sseexp.Variable):
        return self.expression.coefficients(model)[variable.index] != 0

    def evaluate(self, assignment: List[float]) -> float:
        return self.expression.evaluate(assignment)
        
    def name(self) -> str:
        return f"{'-' if self.coefficient < 0 else ''}z"

    def is_equivalent(self, other: Objective, model: ssmod.Model) -> bool:
        return self.type == other.type and \
               self.coefficient == other.coefficient and \
               self.expression.is_equivalent(other.expression, model)

    def __str__(self) -> str:
        return f'{self.type}: {self.name()} = {self.expression}'