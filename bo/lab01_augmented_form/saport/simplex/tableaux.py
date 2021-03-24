from __future__ import annotations
from typing import List
from numpy.typing import ArrayLike
import numpy as np

from . import model as ssmod

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
        cost_factors() -> numpy.Array:
            returns a vector containing factors in the cost row
        cost() -> float:
            returns the cost of solution represented in tableaux
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

    def cost_factors(self) -> ArrayLike:
        return self.table[0,:-1] 

    def cost(self) -> float:
        return self.table[0, -1]

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
        basis = [-1 for _ in range(rows_n -1)]
        for c in range(cols_n - 1):
            column = self.table[:,c]
            belongs_to_basis = column.min() == 0.0 and column.max() == 1.0 and column.sum() == 1.0
            if belongs_to_basis:
                row = np.where(column == 1.0)[0][0]
                # [row-1] because we ignore the cost variable in the basis
                basis[row-1] = c
        return basis

    def __str__(self) -> str:
        def cell(x: float, w: int) -> str:
            return '{0: >{1}}'.format(x, w)

        cost_name = self.model.objective.name()
        basis = self.extract_basis()
        header = ["basis", cost_name] + [var.name for var in self.model.variables] + ["b"]
        longest_col = max([len(h) for h in header])

        rows = [[cost_name]] + [[self.model.variables[i].name] for i in basis]

        for (i,r) in enumerate(rows):
            cost_factor = 0.0 if i > 0 else 1.0
            r += ["{:.3f}".format(v) for v in [cost_factor] + list(self.table[i])]
            longest_col = max(longest_col, max([len(v) for v in r]))

        header = [cell(h, longest_col) for h in header]
        rows = [[cell(v, longest_col) for v in row] for row in rows]

        cell_sep = " | "

        result = cell_sep.join(header) + "\n"
        for row in rows:
            result += cell_sep.join(row) + "\n"
        return result