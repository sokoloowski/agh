from ..abstractsolver import AbstractSolver
from ..model import Solution, Item
from typing import List


class AbstractBnbSolver(AbstractSolver):
    """
    An abstract branch-and-bound solver for the knapsack problems.

    Methods:
    --------
    upper_bound(left : List[Item], solution: Solution) -> float:
        given the list of still available items and the current solution,
        calculates the linear relaxation of the problem
    """

    def upper_bound(self, left: List[Item], solution: Solution) -> float:
        # TODO: implement the linear relaxation, i.e. assume you can take
        #      fraction of the items in the backpack
        #      return the value of such a solution
        #      tip 1. solution is your "starting point" (items already in the backpack)
        #      tip 2. left is the list of items you can still take
        #      tip 3. take the items with highest value density first (as in greedy_density approach)
        #return max(left, key=lambda item: float(item.value / item.weight) * (self.problem.capacity - solution.weight) / item.weight).value + solution.value
        available_weight = self.problem.capacity - solution.weight
        upper_bound = solution.value
        available_items = sorted(left, key=lambda item: item.value/item.weight, reverse=True)
        #available_items = left
        for item in available_items:
            if available_weight >= item.weight:
                upper_bound += item.value
                available_weight -= item.weight
            else:
                upper_bound += available_weight / item.weight * item.value
                break
        return upper_bound


    def solve(self) -> Solution:
        raise Exception("this is an abstract solver, don't try to run it!")
