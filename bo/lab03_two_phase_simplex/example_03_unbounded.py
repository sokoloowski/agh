import logging
from saport.simplex.model import Model


def create_model() -> Model:
    model = Model("example_03_unbounded")

    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")
    x3 = model.create_variable("x3")

    model.add_constraint(x1 - x2 * 3 + x3 * 2 >= 10)
    model.add_constraint(x1 + x2 * 5 - x3 <= -7)

    model.maximize(x1 * 5 + x2 * 2)

    return model


def run():
    model = create_model()

    solution = model.solve()
    if solution.is_bounded:
        raise AssertionError("Your algorithm found a solution to an unbounded problem. This shouldn't happen...")
    else:
        logging.info("Congratulations! This problem is unbounded and your algorithm has found that :)")


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format='%(message)s')
    run()
