import logging
from saport.simplex.model import Model


def create_model() -> Model:
    model = Model("example_02_solvable")

    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")
    x3 = model.create_variable("x3")

    model.add_constraint(x1 + x2 * 3 + x3 * 2 <= 10)
    model.add_constraint(-x1 - x2 * 5 - x3 >= -8)

    model.minimize(-x1 * 8 - x2 * 10 - x3 * 7)

    return model


def run():
    model = create_model()

    try:
        solution = model.solve()
    except:
        raise AssertionError("This problem has a solution and your algorithm hasn't found it!")

    logging.info(solution)

    assert (solution.assignment(model) == [8.0, 0.0, 0.0]), "Your algorithm found an incorrect solution!"

    logging.info("Congratulations! This solution seems to be alright :)")


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO, format='%(message)s')
    run()
