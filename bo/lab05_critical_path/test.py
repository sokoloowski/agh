import saport.critical_path.model as model
import saport.critical_path.solution as sol
import saport.critical_path.solvers.simplex_solver_min as ssmin
import saport.critical_path.solvers.simplex_solver_max as ssmax
import saport.critical_path.solvers.networkx_solver as nxs
import saport.critical_path.solvers.cpm_solver as cpms
import glob

TEST_DIR = "test_projects"

def check(path: str):

    def soft_assert(succ: bool, error: str) -> int:
        if not succ:
            print(error)
            return 1
        return 0

    error_count = 0
    project = model.Project.from_file(path)
    expected = sol.FullSolution.expected_solution_from_file(path)

    simplex_solver_max = ssmax.Solver(project)
    simplex_solver_max_solution = simplex_solver_max.solve()

    simplex_solver_min = ssmin.Solver(project)
    simplex_solver_min_solution = simplex_solver_min.solve()

    networkx_solver = nxs.Solver(project)
    networkx_solver_solution = networkx_solver.solve()

    cpm_solver = cpms.Solver(project)
    cpm_solution = cpm_solver.solve()
    error_count += soft_assert(networkx_solver_solution.duration == expected.duration, f"* networkx solver found incorrect critical path length for {path}: found {networkx_solver_solution.duration}, expected {expected.duration}")
    error_count += soft_assert(simplex_solver_max_solution.duration == expected.duration, f"* simplex max solver found incorrect critical path length for {path}: found {simplex_solver_max_solution.duration}, expected {expected.duration}")
    error_count += soft_assert(simplex_solver_min_solution.duration == expected.duration, f"* simplex min solver found incorrect critical path length for {path}: found {simplex_solver_min_solution.duration}, expected {expected.duration}")
    error_count += soft_assert(cpm_solution.duration == expected.duration, f"* cpm solver found incorrect critical path length for {path}: found {cpm_solution.duration}, expected {expected.duration}")
    error_count += soft_assert(cpm_solution.duration == expected.duration, f"* cpm solver found incorrect critical path length for {path}: found {cpm_solution.duration}, expected {expected.duration}")
    for cp in expected.critical_paths:
        error_count += soft_assert(cp in cpm_solution.critical_paths, f"* cpm solver missed a possible critical path for {path}: found {cpm_solution.critical_paths}, expected {cp}")
    for cp in cpm_solution.critical_paths:
        error_count += soft_assert(cp in expected.critical_paths, f"* cpm solver found an incorrect critical path for {path}: found {cp}, expected {expected.critical_paths}")
    error_count += soft_assert(cpm_solution.task_slacks == expected.task_slacks, f"* cpm solver found incorrect slacks for {path}: found {cpm_solution.task_slacks}, expected {expected.task_slacks}")
    return error_count

if __name__ == "__main__":
    assert_error_count = 0
    for path in glob.glob(TEST_DIR + "/*.txt"):
        assert_error_count += check(path)

    if assert_error_count == 0:
        print("Congrats! Everything seems to be working correctly!")
    else:
        print(f"Sorry :( You still have {assert_error_count} errors to fix")

    

