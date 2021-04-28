from ..abstractsolver import AbstractSolver
from ..model import Solution, Item
from typing import List


class DFSSolver(AbstractSolver):
    """
    Basic DFS solver for the knapsack problems
    """

    def dfs(self):
        self.best_solution = Solution.empty()
        left = self.problem.items
        solution = Solution.empty()
        self._dfs(left, solution)

    def _dfs(self, left: List[Item], solution: Solution):
        if len(left) == 0:
            if solution.value > self.best_solution.value:
                self.best_solution = solution
            return

        if self.timeout():
            self.interrupted = True
            return

        space_left = self.problem.capacity - solution.weight
        item, new_left = left[0], left[1:]

        if item.weight <= space_left:
            self._dfs(new_left, solution.with_added_item(item))
        self._dfs(new_left, solution)

    def solve(self) -> Solution:
        self.start_timer()
        self.interrupted = False
        self.dfs()
        self.best_solution.optimal = not self.interrupted
        self.stop_timer()
        return self.best_solution
