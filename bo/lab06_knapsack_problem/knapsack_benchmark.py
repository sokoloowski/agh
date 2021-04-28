from saport.knapsack.model import Problem
from saport.knapsack.solverfactory import SolverType, SolverFactory
from typing import List, Callable
import os
# manipulate following parameters to customize the benchmarks


class KnapsackBenchmark:
    def __init__(self,
                 problems: List[str],
                 timelimit: int = 60,
                 solver_types: List[SolverType] = list(SolverType),
                 print_function: Callable = print,
                 problems_dir: str = "knapsack_problems"):
        self.timelimit = timelimit
        self.problems = problems
        self.solver_types = solver_types
        self.print_function = print_function
        self.problems_dir = problems_dir

    def print_table(self, table_to_print):
        def cell(x, w):
            return '{0: >{1}}'.format(x, w)

        longest_value = max([len(s) for row in table_to_print for s in row])
        formatted_table_to_print = [[cell(v, longest_value) for v in row] for row in table_to_print]

        self.print_function('-' * (longest_value + 1) * (len(table_to_print[0]) + 1))
        for row in formatted_table_to_print:
            self.print_function(" | ".join(row))
        self.print_function('-' * (longest_value + 1) * (len(table_to_print[0]) + 1))

    def run(self):
        results_table = [[] for _ in self.problems]
        ranking = [[0 for _ in self.solver_types] for _ in self.solver_types]

        for (i, p) in enumerate(self.problems):
            self.print_function(f"* going for {p}", end='\r')
            problem = Problem.from_path(os.path.join(self.problems_dir, p))
            solvers = [SolverFactory.solver(st, problem, self.timelimit) for st in self.solver_types]
            solutions = [(s.solve(), s.total_time) for s in solvers]
            results = [f'{"*" if s.optimal else ""}{s.value}({t:.4f}s)' for (s, t) in solutions]
            results_table[i] = results

            for (i, sol1) in enumerate(solutions):
                for j in range(i + 1, len(solutions)):
                    s1, t1 = sol1
                    s2, t2 = solutions[j]

                    change = 0
                    if s1.optimal != s2.optimal:
                        change = 1 if s1.optimal else -1
                    elif s1.value != s2.value:
                        change = 1 if s1.value > s2.value else -1
                    elif t1 != t2:
                        change = 1 if t1 < t2 else -1

                    ranking[i][j] = ranking[i][j] + change
                    ranking[j][i] = ranking[j][i] - change

        for i in range(len(self.solver_types)):
            for j in range(len(self.solver_types)):
                if i == j:
                    ranking[i][j] = "--"
                else:
                    ranking[i][j] = f"{int(((ranking[i][j] / len(self.problems) + 1)) * 50)}%"

        results_header = ["<results>"] + [st.value for st in self.solver_types]
        table_to_print = [results_header]
        for (i, p) in enumerate(self.problems):
            table_to_print.append([p] + results_table[i])

        self.print_table(table_to_print)

        ranking_header = ["<win ratio>"] + [st.value for st in self.solver_types]
        ranking_to_print = [ranking_header]
        for (i, st) in enumerate(self.solver_types):
            ranking_to_print.append([st.value] + ranking[i])

        self.print_table(ranking_to_print)
