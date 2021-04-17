import numpy as np
from .model import Assignment, AssignmentProblem, NormalizedAssignmentProblem
from typing import List, Dict, Tuple, Set
from numpy.typing import ArrayLike

class Solver:
    '''
    A hungarian solver for the assignment problem.

    Methods:
    --------
    __init__(problem: AssignmentProblem):
        creates a solver instance for a specific problem
    solve() -> Assignment:
        solves the given assignment problem
    extract_mins(costs: ArrayLike):
        substracts from columns and rows in the matrix to create 0s in the matrix
    find_max_assignment(costs: ArrayLike) -> Dict[int,int]:
        finds the biggest possible assinments given 0s in the cost matrix
        result is a dictionary, where index is a worker index, value is the task index
    add_zero_by_crossing_out(costs: ArrayLike, partial_assignment: Dict[int,int])
        creates another zero(s) in the cost matrix by crossing out lines (rows/cols) with zeros in the cost matrix,
        then substracting/adding the smallest not crossed out value
    create_assignment(raw_assignment: Dict[int, int]) -> Assignment:
        creates an assignment instance based on the given dictionary assignment
    '''

    def __init__(self, problem: AssignmentProblem):
        self.problem = NormalizedAssignmentProblem.from_problem(problem)

    def solve(self) -> Assignment:
        costs = np.array(self.problem.costs)
        while True:
            self.extracts_mins(costs)
            max_assignment = self.find_max_assignment(costs)
            if len(max_assignment) == self.problem.size():
                return self.create_assignment(max_assignment)
            self.add_zero_by_crossing_out(costs, max_assignment)

    def extracts_mins(self, costs: ArrayLike):
        for row in costs:
            row -= np.min(row)
        for col in costs.T:
            col -= np.min(col)

    def add_zero_by_crossing_out(self, costs: ArrayLike, partial_assignment: Dict[int, int]):
        marked_rows = []
        marked_cols = []
        workers, tasks = np.shape(costs)
        for i in range(workers):
            if i not in partial_assignment.keys():
                marked_rows.append(i)
        while True:
            finish = True
            for i in range(tasks):
                for j in marked_rows:
                    if costs[j, i] == 0 and i not in marked_cols:
                        marked_cols.append(i)
                        finish = False
                        break
            if finish:
                break
            for i in marked_cols:
                for j in range(workers):
                    if j not in marked_rows and partial_assignment[j] == i:
                        marked_rows.append(j)
        crossed_rows = [row for row in range(workers) if row not in marked_rows]
        not_crossed_rows = marked_rows
        not_crossed_cols = [col for col in range(tasks) if col not in marked_cols]
        crossed_cols = marked_cols
        min_in_not_crossed = costs[not_crossed_rows[0], not_crossed_cols[0]]
        for row in not_crossed_rows:
            for col in not_crossed_cols:
                if costs[row, col] < min_in_not_crossed:
                    min_in_not_crossed = costs[row, col]
        costs -= min_in_not_crossed
        for row in crossed_rows:
            costs[row, :] += min_in_not_crossed
        for col in crossed_cols:
            costs[:, col] += min_in_not_crossed

    def find_max_assignment(self, costs) -> Dict[int, int]:
        partial_assignment = dict()
        n_workers, n_tasks = np.shape(costs)
        r = [[] for i in range(n_workers)]
        c = [[] for i in range(n_tasks)]
        for i in range(n_workers):
            for j in range(n_tasks):
                if costs[i, j] == 0:
                    r[i].append(j)
                    c[j].append(i)
        for i in range(n_workers):
            minimum_zero_number_in_row = np.inf
            row_with_min_zeros = -1
            for row, row_list in enumerate(r):
                number_of_zeros = len(row_list)
                if (number_of_zeros < minimum_zero_number_in_row) and (number_of_zeros != 0):
                    minimum_zero_number_in_row = number_of_zeros
                    row_with_min_zeros = row
            if row_with_min_zeros == -1:
                break
            minimum_zero_number_in_col = np.inf
            col_with_min_zeros = -1
            for col in r[row_with_min_zeros]:
                number_of_zeros = len(c[col])
                if (number_of_zeros < minimum_zero_number_in_col) and (number_of_zeros != 0):
                    minimum_zero_number_in_col = number_of_zeros
                    col_with_min_zeros = col
            r[row_with_min_zeros].clear()
            if col_with_min_zeros == -1:
                continue
            partial_assignment[row_with_min_zeros] = col_with_min_zeros
            for row in r:
                if col_with_min_zeros in row:
                    row.remove(col_with_min_zeros)
            for col in c:
                if row_with_min_zeros in col:
                    col.remove(row_with_min_zeros)
        print(partial_assignment)
        return partial_assignment

    def create_assignment(self, raw_assignment: Dict[int, int]) -> Assignment:
        workers, tasks = np.shape(self.problem.original_problem.costs)
        assignment = [-1 for i in range(workers)]
        for key in raw_assignment.keys():
            if key < workers and raw_assignment[key] < tasks:
                assignment[key] = raw_assignment[key]
        total_cost = 0
        for worker, task in enumerate(assignment):
            if task != -1:
                total_cost += self.problem.original_problem.costs[worker, task]
        return Assignment(assignment, total_cost)
