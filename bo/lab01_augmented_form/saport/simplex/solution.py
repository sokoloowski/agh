from __future__ import annotations
from typing import List

from . import model as ssmod
from . import tableaux as sstab

class Solution:
    """
        A class to represent a solution to linear programming problem.

        Attributes
        ----------
        model : Model
            model corresponding to the solution
        tableaux: Tableaux
            a simplex tableaux corresponding to the first base solution  

        Methods
        -------
        __init__( model: Model, tableaux: Tableaux):
            constructs a new solution for the specified model and tableaux
    """
    model: ssmod.Model
    tableaux: sstab.Tableaux 

    def __init__(self, model: ssmod.Model, tableaux: sstab.Tableaux):
        self.model = model 
        self.tableaux = tableaux

    def __str__(self):
        output = "- augmented model:\n"
        output += f"{self.tableaux.model}\n----------"
        output += "- tableaux:\n"
        output += f"{self.tableaux}"
        return output

