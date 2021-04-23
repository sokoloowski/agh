# How to use SAPORT?

# 1. Import the library
from saport.simplex.model import Model 

# 2. Create a model
model = Model("example")

# 3. Add variables
x1 = model.create_variable("x1")
x2 = model.create_variable("x2")
x3 = model.create_variable("x3")

# 4. FYI: You can create expression and evaluate them
expr1 = 0.16 * x1 - 0.94 * x2 + 0.9 * x3
print(f"Value of the expression for the specified assignment is  {expr1.evaluate([1, 1, 2])}\n")

# 5. Then add constraints to the model
model.add_constraint(expr1 <= 1200)
model.add_constraint(0.2 * x2 + 0.3 * x2 + 0.3 * x3 + 0.1 * x1 <= 600)

# 6. Set the objective!
model.minimize(1.1 * x1 + 3.4 * x2 + 2.2 * x3)

# 7. You can print the model
print("Before solving:")
print(model)

# 8. And finally solve it!
solution = model.solve()

# 9. Model is being simplified before being solver
print("After solving:")
print(model)

# 10. Print solution (uncomment after finishing assignment)
# print("Solution: ")
# print(solution)





