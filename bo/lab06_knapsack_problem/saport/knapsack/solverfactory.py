from __future__ import annotations
from .model import Problem
from enum import Enum
from collections import defaultdict
from .abstractsolver import AbstractSolver
from .solvers.bnb_dfs import BnbDFSSolver
from .solvers.dfs import DFSSolver
from .solvers.dynamic import DynamicSolver
from .solvers.greedy_density import GreedySolverDensity
from .solvers.greedy_value import GreedySolverValue
from .solvers.greedy_weight import GreedySolverWeight


class SolverType(Enum):
    """
    An enum representing all the available solver types.
    """
    GREEDY_VALUE = "greedy(value)"
    GREEDY_WEIGHT = "greedy(weight)"
    GREEDY_DENSITY = "greedy(density)"
    DYNAMIC = "dynamic"
    DFS = "dfs"
    BRANCH_AND_BOUND_DFS = "bnb(dfs)"


class SolverFactory:
    """
    A factory class creating solver objects.

    Static Methods:
    ---------------
    solver(type: SolverType, problem: Problem, timelimit: int) ->  AbstractSolver:
        creates a new solver object based on the specified type, given problem and timelimit
    """
    @staticmethod
    def solver(type: SolverType, problem: Problem, timelimit: int) -> AbstractSolver:
        return defaultdict(
            AbstractSolver, {
                SolverType.GREEDY_VALUE: GreedySolverValue,
                SolverType.GREEDY_WEIGHT: GreedySolverWeight,
                SolverType.GREEDY_DENSITY: GreedySolverDensity,
                SolverType.DYNAMIC: DynamicSolver,
                SolverType.DFS: DFSSolver,
                SolverType.BRANCH_AND_BOUND_DFS: BnbDFSSolver,
            })[type](problem, timelimit)
