import saport.assignment.model as sam
import saport.assignment.hungarian_solver as sahs
import saport.assignment.simplex_solver as sass

TEST_DIR = "assignment_tests"
MIN = ["square_min_03_15", "square_min_04_22", "square_min_05_173"]
RECT = ["square_min_03_04_14", "square_min_04_03_14"]
MAX = ["square_max_04_41", "square_max_04_03_24"]

def check(path: str, expected_value: int, description: str):
    model = sam.AssignmentProblem.from_file(path)
    hungarian_solver = sahs.Solver(model)
    simplex_solver = sass.Solver(model)

    hungarian_solution = hungarian_solver.solve()
    simplex_solution = simplex_solver.solve()

    assert hungarian_solution.objective == expected_value, f"hungarian solver found incorrect solution cost for {description} at {path}: found {hungarian_solution.objective}, expected {expected}"
    assert simplex_solution.objective == expected_value, f"simplex solver found incorrect solution cost for {description} at {path}: found {simplex_solution.objective}, expected {expected}"

    hungarian_recalculated_cost = sum([model.costs[w,t] for w,t in enumerate(hungarian_solution.assigned_tasks) if t >= 0])
    simplex_recalculated_cost = sum([model.costs[w,t] for w,t in enumerate(simplex_solution.assigned_tasks) if t >= 0])

    assert hungarian_recalculated_cost == expected_value, f"hungarian solver found incorrect assignment for {description} at {path}"
    assert simplex_recalculated_cost == expected_value, f"simplex solver found incorrect assignment for {description} at {path}"

if __name__ == "__main__":

    # TESTING STANDARD SQUARE MIN ASSIGNMENTS
    for fname in MIN:
        expected = (int)(fname.split("_")[-1])
        check(f"{TEST_DIR}/{fname}.txt", expected, "standard square minimization problem")

    # TESTING RECTANGULAR MIN ASSIGNMENTS (NUMBER OF TASKS != NMBER OF WORKERS)
    for fname in RECT:
        expected = (int)(fname.split("_")[-1])
        check(f"{TEST_DIR}/{fname}.txt", expected, "rectangular minimization problem")

    # TESTING MAX ASSIGNMENTS
    for fname in MAX:
        expected = (int)(fname.split("_")[-1])
        check(f"{TEST_DIR}/{fname}.txt", expected, "rectangular maximization problem")

    print("Success! Your assignment problem solvers operate correctly!")

    