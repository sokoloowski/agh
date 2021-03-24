import logging
from saport.simplex.model import Model

def create_model() -> Model:
    model = Model(__file__)

    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")

    model.add_constraint(x1 >= 150)
    model.add_constraint(x2 >= 250)
    model.add_constraint(x1 * 2 + x2 >= 500)

    model.maximize(x1 * 8 + x2 * 5)

    return model


def run():
    model = create_model()

    try:
        solution = model.solve()
    except:
        raise AssertionError("This problem has a solution and your algorithm hasn't found it!")

    logging.info(solution)

    assert (solution.is_bounded == False), "Your algorithm found an incorrect solution!"

    logging.info("Congratulations! This solution seems to be alright :)")


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format='%(message)s')
    run()