import sys
from .model import Problem, Solution
from time import time


class AbstractSolver:
    """
        An abstract class to solve knapsack problems 


        Attributes
        ----------
        problem : Problem
            knapsack problem to be solved
        timelimit: int
            what is the maximal solving time (in seconds)
        total_time: float
            how long it took to solve the problem
        start_time: float
            when the solving started

        Methods
        -------
        start_timer():
            remember the starting time for the solver
        stop_timer():
            stores the total solving time
        wall_time() -> float:
            returns how long solver has been working
        timeut() -> bool:
            whether solver should stop working due to the timeout

        __init__(problem: Problem, timelimit: int):
            initialized object with the given attributes
        solve() -> Solution:
            solves the knapsack problem
    """
    def start_timer(self):
        self.start_time = time()

    def stop_timer(self):
        self.total_time = self.wall_time()

    def wall_time(self) -> float:
        return time() - self.start_time

    def timeout(self) -> bool:
        return self.wall_time() > self.timelimit

    def __init__(self, problem: Problem, timelimit: int):
        self.problem = problem
        self.timelimit = timelimit
        self.total_time = None
        self.start_time = None
        self.interrupted = False
        self.best_solution = None

    def solve(self) -> Solution:
        raise Exception("abstract solver shouldn't be called!")
