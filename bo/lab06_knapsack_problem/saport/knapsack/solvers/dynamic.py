from ..abstractsolver import AbstractSolver
from ..model import Solution
from numpy.typing import ArrayLike
import numpy as np
from typing import Tuple


class DynamicSolver(AbstractSolver):
    """
    A naive dynamic programming solver for the knapsack problem.
    """

    def create_table(self) -> ArrayLike:
        # TODO: fill the table!
        # tip 1. init table using np.zeros function
        # tip 2. remember to handle timeout (refer to the dfs solver for an example)
        #        - just return the current state of the table
        capacity = self.problem.capacity
        items = self.problem.items
        n_items = len(items)
        table = np.zeros((capacity+1, n_items+1))
        # if self.timeout():
        #     self.interrupted = True
        #     return table

        for n in range(1, n_items + 1):
            item = items[n-1]
            for c in range(capacity+1):
                if item.weight <= c:
                    table[c, n] = max(table[c-item.weight, n-1]+item.value, table[c, n-1])
                else:
                    table[c, n] = table[c, n-1]
                if self.timeout():
                    self.interrupted = True
                    return table

        return table

    def extract_solution(self, table: ArrayLike) -> Solution:
        used_items = []
        optimal = table[-1, -1] > 0
        c = self.problem.capacity
        items = self.problem.items
        n_items = len(items)

        # TODO: extract taken items from the table!
        n = n_items
        while n:
            if table[c, n] != table[c, n-1]:
                used_items.append(items[n-1])
                c -= items[n-1].weight
            n -= 1

        return Solution.from_items(used_items, optimal)

    def solve(self) -> Tuple[Solution, float]:
        self.interrupted = False
        self.start_timer()

        table = self.create_table()
        solution = self.extract_solution(table) if table is not None else Solution.empty()

        self.stop_timer()
        return solution
