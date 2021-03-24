from __future__ import annotations
from copy import deepcopy
from typing import Iterable, List

from itertools import groupby
from functools import reduce
import saport.simplex.expressions.constraint as ssecon
import saport.simplex.model as ssmod

class Expression:
    """
        A class to represent a linear polynomial in the linear programming, i.e. a sum of atom (e.g. 4x + 5y - 0.4z)

        Attributes
        ----------
        atoms : list[Atom]
            list of the atoms in the polynomial

        Methods
        -------
        __init__(*atoms : *Atom) -> Expression:
            constructs an expression with atoms given in the paremeter list
        @classmethod from_vectors(variables : Iterable[Variable], coefficients: Iterable[float]) -> Expression:
            constructs an expression with collections of coefficients and corresponding variables
        evaluate(assignment: List[float]) -> float:
            returns value of the expression for the given assignment
            assignment is just a list of values with order corresponding to the variables in the model
        simplified() -> Expression:
            returns a new expression with sorted and atoms and reduced coefficients 
        coefficients(model: Model) -> list[float]:
            return list of coefficients corresponding to the variables in the model
        is_equivalent(other: Expression, model: Model) -> bool:
            returns true if other expression is equivalent given the specific model
        __add__(other: Expression) -> Expression:
            returns sum of the two polynomials
        __sub__(other: Expression) -> Expression:
            returns sum of the two polynomials, inverting the first atom in the second polynomial
            useful for expressions like 3*x - 4y, otherwise one would have to write 3*x + -4*y 
        __mul__(coefficient: float) -> Expression:
            return a new polynomial with all coefficients multiplied by the given number
        __eq__(bound: float) -> Constraint:
            returns a new equality constraint
        __le__(bound: float) -> Constraint:
            returns a new "less than or equal" constraint
        __ge__(bound: float) -> Constraint:
            returns a new "greater than or equal" constraint
    """
    atoms: List[Atom]

    def __init__(self, *atoms: Atom):
        self.atoms = atoms 

    @classmethod
    def from_vectors(self, variables: Iterable[Variable], coefficients: Iterable[float]) -> Expression:
        assert len(variables) == len(coefficients), f"number of coefficients should correspond to variables in the expression"
        atoms = [Atom(v,f) for (v,f) in zip(variables, coefficients)]
        return Expression(*atoms)

    def evaluate(self, assignment: List[float]) -> float:
        adder = lambda val, a: val + a.evaluate_with_value(assignment[a.var.index])
        return reduce(adder, self.atoms, 0) 

    def simplify(self):
        projection = lambda a: a.var.index
        reduce_atoms = lambda a1, a2: Atom(a1.var, a1.coefficient + a2.coefficient)
        reduce_group = lambda g: reduce(reduce_atoms, g[1:], g[0])
    
        sorted_atoms = sorted(self.atoms, key=projection)
        grouped_atoms = [list(g[1]) for g in groupby(sorted_atoms, key=projection)]
 
        self.atoms = [reduce_group(g) for g in grouped_atoms]
        
    def coefficients(self, model: ssmod.Model) -> List[float]:
        simplified_expression = deepcopy(self)
        simplified_expression.simplify()
        coefficients = [0.0 for _ in model.variables]
        for a in simplified_expression.atoms:
            if a.var.index < len(coefficients):
                coefficients[a.var.index] = a.coefficient
        return coefficients

    def is_equivalent(self, other: Expression, model: ssmod.model) -> bool:
        return self.coefficients(model) == other.coefficients(model)

    def __add__(self, other: Expression) -> Expression:
        new_atoms = list(self.atoms)
        new_atoms += other.atoms;
        return Expression(*new_atoms)

    def __sub__(self, other: Expression) -> Expression:
        return self.__add__(other * -1)

    def __neg__(self) -> Expression:
        return self.__mul__(-1)

    def __mul__(self, coefficient: float) -> Expression:
        new_atoms = [a * coefficient for a in self.atoms]
        return Expression(*new_atoms)

    __rmul__ = __mul__

    def __eq__(self, bound: float) -> ssecon.Constraint:
        return ssecon.Constraint(self, bound, ssecon.ConstraintType.EQ)
    
    def __ge__(self, bound: float) -> ssecon.Constraint:
        return ssecon.Constraint(self, bound, ssecon.ConstraintType.GE)

    def __le__(self, bound: float) -> ssecon.Constraint:
        return ssecon.Constraint(self, bound, ssecon.ConstraintType.LE)

    def __str__(self) -> str:
        text = str(self.atoms[0])
        
        for atom in self.atoms[1:]:
            text += ' + ' if atom.coefficient >= 0 else ' - '
            coefficient = "" if abs(atom.coefficient) == 1.0 else f"{abs(atom.coefficient)}*"
            text += f'{coefficient}{atom.var.name}'
        return text

class Atom(Expression):
    """
        A class to represent an atom of the linear programming expression, i.e. variable and it's coefficient (e.g. 4x, -5.3x, etc.)
        It derives from the Expression class and can be intepreted as a expression containing only single atom, itself

        Attributes
        ----------
        var : Variable
            variable associated with the atom
        coefficient : float
            coefficient value associated with the atom

        Methods
        -------
        __init__(var: Variable, coefficient: float) -> Atom:
            constructs new atom with a specified variable and coefficient
        evaluate(assigned_value: float) -> float:
            returns value of the atom for the given assignment
        __mul__(coefficient: float) -> Atom:
            return new atom with a multiplied coefficient
    """
    var: Variable
    coefficient: float

    def __init__(self, var: Variable, coefficient: float):
        self.var = var 
        self.coefficient = float(coefficient)
        super().__init__(self)

    def evaluate_with_value(self, assigned_value: float) -> float:
        return self.coefficient * assigned_value

    def evaluate(self, assignment: List[float]) -> float:
        return super().evaluate(assignment)

    def __mul__(self, coefficient: float) -> Atom:
        return Atom(self.var, self.coefficient * coefficient)

    __rmul__ = __mul__

    def __str__(self):
        if (float(self.coefficient) == 1.0):
            return str(self.var) 
        elif (float(self.coefficient) == -1.0):
            return f"-{self.var}"
        else:
            return f"{self.coefficient}*{self.var}"

class Variable(Atom):
    """
        A class to represent a linear programming variable.
        It derives from the Atom class and can be interpreted as Atom with coefficient = 1.

        Attributes
        ----------
        name : str
            name of the variable
        index : int
            index of the variable used in the model
        type : VariableType
            type of the variable

        Methods
        -------
        __init__(name: str, index: int) -> Variable:
            constructs new variable with a specified name and index
    """
    name: str
    index: int 

    def __init__(self, name: str, index: int):
        self.name = name
        self.index = index
        super().__init__(self, 1)

    def __str__(self) -> str:
        return self.name

    def __key__(self) -> Tuple[str, int]:
        return (self.name, self.index)

    def __hash__(self) -> int:
        return hash(self.__key__())

    def __eq__(self, other: Variable) -> bool:
        if isinstance(other, Variable):
            return self.__key__() == other.__key__()
        return NotImplemented