from knapsack_benchmark import KnapsackBenchmark
from saport.knapsack.solverfactory import SolverType

problems = [
    "ks_4_0", "ks_19_0", "ks_40_0", "ks_50_0",
    "ks_60_0", "ks_100_0", "ks_200_0", "ks_500_0"
]

benchmark = KnapsackBenchmark(
    problems,
    solver_types=[
        # solvers to be benchmarked
        SolverType.GREEDY_VALUE,
        SolverType.GREEDY_WEIGHT,
        SolverType.GREEDY_DENSITY,
        SolverType.DYNAMIC,
        SolverType.BRANCH_AND_BOUND_DFS,
        SolverType.DFS,
    ],
)
benchmark.run()
