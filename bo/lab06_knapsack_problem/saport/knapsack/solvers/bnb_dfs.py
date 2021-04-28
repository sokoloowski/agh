from .bnb import AbstractBnbSolver
from ..model import Solution, Item
from typing import List


class BnbDFSSolver(AbstractBnbSolver):
    """
    A branch-and-bound solver for the Knapsack Problem,
    explores the search tree using a basic DFS strategy.
    """

    def dfs_bnb(self):
        self.best_solution = Solution.empty()
        return self._dfs_bnb(self.problem.items, self.best_solution)

    def _dfs_bnb(self, left: List[Item], solution: Solution):
        # TODO: implement a dfs branch-and-bound solver
        #
        #   tip 1. use the DFS code as your starting point (dfs.py)
        #   tip 2. use the upper_bound method to calculate the upper bound
        #          (implement it first in the bnb.py file)
        #   tip 3. if the upper bound is lower than the current best solution, just
        #          ignore rest of the branch (a simple "return" is enough)
        if len(left) == 0:
            if solution.value > self.best_solution.value:
                self.best_solution = solution
            return

        if self.upper_bound(left, solution) < self.best_solution.value:
            return

        if self.timeout():
            self.interrupted = True
            return

        space_left = self.problem.capacity - solution.weight
        item, new_left = left[0], left[1:]

        if item.weight <= space_left:
            self._dfs_bnb(new_left, solution.with_added_item(item))
        self._dfs_bnb(new_left, solution)

        return

    def solve(self) -> Solution:
        self.interrupted = False
        self.start_timer()
        self.dfs_bnb()
        self.best_solution.optimal = not self.interrupted
        self.stop_timer()
        return self.best_solution
