import numpy as np
from .model import AssignmentProblem, Assignment, NormalizedAssignmentProblem
from ..simplex.model import Model
from ..simplex.expressions.expression import Expression
from dataclasses import dataclass
from typing import List

class Solver:
    '''
    A simplex solver for the assignment problem.

    Methods:
    --------
    __init__(problem: AssignmentProblem):
        creates a solver instance for a specific problem
    solve() -> Assignment:
        solves the given assignment problem
    '''

    def __init__(self, problem: AssignmentProblem):
        self.problem = NormalizedAssignmentProblem.from_problem(problem)

    def solve(self) -> Assignment:
        model = Model("assignment")
        size = self.problem.size()
        for worker in range(size):
            for task in range(size):
                var = model.create_variable(f"c{worker}{task}")
                model.add_constraint(var <= 1)
                if not worker and not task:
                    objective = var * self.problem.costs[worker][task]
                else:
                    objective += var * self.problem.costs[worker][task]
        for i in range(size):
            var = model.variables[i]
            model.add_constraint(var <= 1)
            model.constraints[size * size + i].type = "="
        for i in range(size):
            var = model.variables[size * i]
            model.add_constraint(var <= 1)
            model.constraints[size * size + size + i].type = "="
        for i in range(size * size):
            col = i % size
            row = i // size
            var = model.variables[i]
            if row:
                model.constraints[size * size + col].expression += var
            if col:
                model.constraints[size * size + size + row].expression += var
        model.minimize(objective)
        solution = model.solve()
        workers = self.problem.original_problem.n_workers()
        tasks = self.problem.original_problem.n_tasks()
        assigned_tasks = [-1 for i in range(workers)]
        for i in range(workers):
            for j in range(tasks):
                if solution.assignment()[i * max(tasks, workers) + j] == 1:
                    assigned_tasks[i] = j
        org_objective = sum([self.problem.original_problem.costs[w,t] for w,t in enumerate(assigned_tasks) if t >= 0])
        return Assignment(assigned_tasks, org_objective)
