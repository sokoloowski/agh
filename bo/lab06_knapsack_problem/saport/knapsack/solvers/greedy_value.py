from .greedy import AbstractGreedySolver
from ..model import Item


class GreedySolverValue(AbstractGreedySolver):
    """
    A greedy solver for the knapsack problems. 
    Uses value as the greedy heuristic. 
    """
    def greedy_heuristic(self, item: Item) -> float:
        # TODO: replace line below with the correct value
        return item.value