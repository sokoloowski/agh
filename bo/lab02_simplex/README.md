# Lab 02 - Simplex

The goal of this is lab is to:

* fill missing code in the `saport.simplex.tableaux.Tableaux` class
* create two models to test the algorithm, filling missing code in the `example_02_solvable.py` and `example_03_unbounded.py` files

## How To Run Tests

*Warning*: to run the tests, you should first implement the simplex algorithm. Otherwise the tests will just hang due to the `pass` methods in the `saport.simplex.solver.Tableaux`.

1. Then install required packages (`numpy` only at the moment): `pip install -r requirements.txt`
2. Then you can run each example separately as an independent program: `python example_01_solvable.py`
3. Or you can ran all the tests: `python test.py`


## SAPORT

SAPORT = Student's Attempt to Produce an Operation Research Toolkit

Refer to the `example.py` for a quick overview of the API.