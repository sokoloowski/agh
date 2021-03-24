from __future__ import annotations
from enum import Enum
from . import expression as sseexp
from .. import model as ssmod

class ConstraintType(Enum):
    """
        An enum to represent a constraint type:
        - LE = less than or equal
        - EQ = equality
        - GR = greater than or equal
    """
    LE = -1
    EQ = 0
    GE = 1

    def __str__(self):
        return {
            ConstraintType.LE: "<=",
            ConstraintType.EQ: "=",
            ConstraintType.GE: ">="
        }[self]

class Constraint:
    """
        A class to represent a constraint in the linear programming expression, e.g. 4x + 5y <= 13, etc.

        Attributes
        ----------
        index : int
            index of the constraint in the model
        expression : Expression
            polynomial expressions that is bounded
        bound : float
            a bound constraining the linear polynomial
        type: ConstraintType
            type of the constraint: LE, EQ, GE

        Methods
        -------
        __init__(expression: Expression, bound: float, type: ConstraintType = ConstraintType.GE) -> Constraint:
            constructs new constraint with a specified polynomial, bound and type
        simplified() -> Constraint:
            returns new constraint with the simplified polynomial
        invert():
            inverts type of the constraint (multiplies constraint times -1)
        is_equivalent(other: Constraint, model: Model) -> bool:
            returns true if other constraint is equivalent given the specific model
    """
    index: int 
    expression: sseexp.Expression
    bound: float 
    type: ConstraintType

    def __init__(self, expression: sseexp.Expression, bound: float, type: ConstraintType = ConstraintType.GE, index: int = None):
        self.index = index
        self.expression = expression
        self.bound = bound
        self.type = type

    def simplify(self):
        self.expression.simplify()

    def invert(self):
        self.type = ConstraintType(self.type.value * -1)
        self.expression = self.expression * -1
        self.bound = self.bound * -1

    def is_equivalent(self, other: Constraint, model: ssmod.Model) -> bool:
        return self.type == other.type and \
               self.bound == other.bound and \
               self.expression.is_equivalent(other.expression, model)

    def __str__(self):
        return f"{self.expression} {self.type} {self.bound}"