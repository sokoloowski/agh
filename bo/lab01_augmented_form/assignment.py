from saport.simplex.model import Model


def assignment_1():
    model = Model("Assignment 1")
    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")
    x3 = model.create_variable("x3")

    expr1 = x1 + x2 + x3
    expr2 = x1 + (x2 * 2) + x3
    expr3 = (x2 * 2) + x3

    model.add_constraint(expr1 <= 30)
    model.add_constraint(expr2 >= 10)
    model.add_constraint(expr3 <= 20)

    model.maximize((x1 * 2) + x2 + (x3 * 3))

    return model


def assignment_2():
    model = Model("Assignment 2")
    p1 = model.create_variable("p1")
    p2 = model.create_variable("p2")
    p3 = model.create_variable("p3")
    p4 = model.create_variable("p4")

    expr1 = (p1 * 0.8) + (p2 * 2.4) + (p3 * 0.9) + (p4 * 0.4)
    expr2 = (p1 * 0.6) + (p2 * 0.6) + (p3 * 0.3) + (p4 * 0.3)

    model.add_constraint(expr1 >= 1200)
    model.add_constraint(expr2 >= 600)

    model.minimize((p1 * 9.6) + (p2 * 14.4) + (p3 * 10.8) + (p4 * 7.2))
    return model


def assignment_3():
    model = Model("Assignment 3")
    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")

    expr1 = (x1 * 5) + (x2 * 15)
    expr2 = (x1 * 20) + (x2 * 5)
    expr3 = (x1 * 15) + (x2 * 2)

    model.add_constraint(expr1 >= 50)
    model.add_constraint(expr2 >= 40)
    model.add_constraint(expr3 <= 60)

    model.minimize((x1 * 8) + (x2 * 4))

    return model


def assignment_4():
    model = Model("Assignment 4")

    # Zadanie 4. Fabryka celulozy i papieru musi wyprodukować co najmniej 150
    # zwojów papieru o szerokości 105 cm, 200 zwojów papieru o szerokości 75 cm i
    # 150 zwojów o szerokości 35 cm. Jako surowiec zostanie użyty papier zrolowany
    # o szerokości 2 m. W jaki sposób fabryka ma zrealizować zamówienie tak, żeby
    # odpad z procesu cięcia był jak najmniejszy?

    # x1 = model.create_variable("x1")
    # x2 = model.create_variable("x2")
    # x3 = model.create_variable("x3")
    #
    # model.add_constraint(x1 * 105 <= 200)
    # model.add_constraint(x2 * 75 <= 200)
    # model.add_constraint(x3 * 35 <= 200)
    #
    # model.minimize((x1 * 150) + (x2 * 200) + (x3 * 150))

    # Second try

    x1 = model.create_variable("x1")
    x2 = model.create_variable("x2")
    x3 = model.create_variable("x3")
    x4 = model.create_variable("x4")
    x5 = model.create_variable("x5")
    x6 = model.create_variable("x6")
    x7 = model.create_variable("x7")
    x8 = model.create_variable("x8")
    x9 = model.create_variable("x9")
    x10 = model.create_variable("x10")
    x11 = model.create_variable("x11")
    x12 = model.create_variable("x12")
    x13 = model.create_variable("x13")
    x14 = model.create_variable("x14")
    x15 = model.create_variable("x15")

    model.add_constraint(x1 + x7 + x9 + x10 >= 150)
    model.add_constraint(x2 + x4 + x5 * 2 + x6 * 3 + x7 + x9 * 2 + x12 + x13 * 2 + x14 * 3 + x15 * 4 + x8 * 5 >= 150)
    model.add_constraint(x3 + x4 + x5 + x6 + x10 + x11 * 2 + x12 * 2 >= 200)

    model.minimize(x1 * 95 + x2 * 165 + x3 * 125 + x4 * 90 + x5 * 55 + x6 * 20 + x7 * 60 + x8 * 25 + x9 * 25 + x10 * 20 + x11 * 50 + x12 * 15 + x13 * 130 + x14 * 95 + x15 * 60)

    return model


# print(assignment_1())
print(assignment_1().solve())
print(assignment_2().solve())
print(assignment_3().solve())
print(assignment_4().solve())
