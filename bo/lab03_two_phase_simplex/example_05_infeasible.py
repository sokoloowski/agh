import logging
from saport.simplex.model import Model

from saport.simplex.model import Model


def create_model() -> Model:
    model = Model("example_05_infeasible")

    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")

    model.add_constraint(x1 >= 150)
    model.add_constraint(x2 >= 250)
    model.add_constraint(x1 * 2 + x2 <= 500)

    model.maximize(x1 * 8 + x2 * 5)

    return model


def run():
    solution = create_model().solve()
    if solution.is_feasible:
        raise AssertionError("Your algorithm found a solution to an infeasible problem. This shouldn't happen...")
    else:
        logging.info("Congratulations! This problem is infeasible and your algorithm has found that :)")


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format='%(message)s')
    run()
