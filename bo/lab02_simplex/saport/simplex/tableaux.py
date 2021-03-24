from __future__ import annotations
from typing import List
from numpy.typing import ArrayLike
import numpy as np
from . import model as ssmod

"""
eps is used to avoid numerical errors, e.g.
- for float equality checks use math.isclose https://docs.python.org/3/library/math.html#math.isclose
- for inequality checks, instead of >= 0 you may just write >= -eps
"""
eps = 1e-09


class Tableaux:
    """
    A class to represent a tableaux to linear programming problem.

    Attributes
    ----------
    model : Model
        model corresponding to the tableaux
    table : numpy.Array
        2d-array with the tableaux

    Methods
    -------
    __init__(model: Model, table: array) -> Tableaux:
        constructs a new tableaux for the specified model and initial table
    objective_coefficients() -> numpy.Array:
        returns a vector containing coefficients in the objective row
    objective_value() -> float:
        returns the objective value of solution represented in tableaux
    is_optimal() -> bool:
        checks whether the current solution is optimal
    choose_entering_variable() -> int:
        finds index of the variable, that should enter the basis next
    is_unbounded(col: int) -> bool:
        checks whether the problem is unbounded
    choose_leaving_variable(col: int) -> int:
        finds index of the variable, that should leave the basis next
    pivot(col: int, row: int):
        updates tableaux using pivot operation with given entering and leaving variables
    extract_assignment() -> List[float]:
        returns assignment corresponding to the tableaux
    extract_basis() -> List[int]
        returns list of indexes corresponding to the variables belonging to the basis
    """

    model: ssmod.Model
    table: ArrayLike

    def __init__(self, model: ssmod.Model, table: ArrayLike):
        self.model = model
        self.table = table

    def objective_coefficients(self) -> ArrayLike:
        return self.table[0, :-1]

    def objective(self) -> float:
        return self.table[0, -1]

    def is_optimal(self) -> bool:
        return all(coefficient >= -eps for coefficient in self.objective_coefficients())

    def choose_entering_variable(self) -> int:
        return np.argmin(self.objective_coefficients())

    def is_unbounded(self, col: int) -> bool:
        return all(coefficient <= eps for coefficient in self.table[1:, col])

    def choose_leaving_variable(self, col: int) -> int:
        with np.errstate(divide='ignore', invalid='ignore'):
            arr = np.divide(self.table[1:, -1], self.table[1:, col])
            arr[~ np.isfinite(arr)] = np.inf
        return np.where(arr > eps, arr, np.inf).argmin() + 1

    def pivot(self, row: int, col: int):
        pivot = self.table[row, col]
        self.table[row, :] /= pivot
        num_rows, num_cols = self.table.shape
        for i in range(num_rows):
            if i != row:
                self.table[i, :] += self.table[row, :] * -self.table[i, col]

    def extract_assignment(self) -> List[float]:
        rows_n, cols_n = self.table.shape
        assignment = [0.0 for _ in range(cols_n - 1)]
        basis = self.extract_basis()
        for r in range(1, rows_n):
            var_index = basis[r - 1]
            assignment[var_index] = self.table[r, -1]

        return assignment

    def extract_basis(self) -> List[int]:
        rows_n, cols_n = self.table.shape
        basis = [-1 for _ in range(rows_n - 1)]
        for c in range(cols_n - 1):
            column = self.table[:, c]
            belongs_to_basis = column.min() == 0.0 and column.max() == 1.0 and column.sum() == 1.0
            if belongs_to_basis:
                row = np.where(column == 1.0)[0][0]
                # [row-1] because we ignore the objective variable in the basis
                basis[row - 1] = c
        return basis

    def __str__(self) -> str:
        def cell(x: float, w: int) -> str:
            return "{0: >{1}}".format(x, w)

        objective_name = self.model.objective.name()
        basis = self.extract_basis()
        header = ["basis", objective_name] + [var.name for var in self.model.variables] + ["b"]
        longest_col = max([len(h) for h in header])

        rows = [[objective_name]] + [[self.model.variables[i].name] for i in basis]

        for i, r in enumerate(rows):
            objective_coefficient = 0.0 if i > 0 else 1.0
            r += ["{:.3f}".format(v) for v in [objective_coefficient] + list(self.table[i])]
            longest_col = max(longest_col, max([len(v) for v in r]))

        header = [cell(h, longest_col) for h in header]
        rows = [[cell(v, longest_col) for v in row] for row in rows]

        cell_sep = " | "

        result = cell_sep.join(header) + "\n"
        for row in rows:
            result += cell_sep.join(row) + "\n"
        return result
