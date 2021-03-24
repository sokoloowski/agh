import importlib
test_modules = ['example_01_solvable', 'example_02_solvable', 'example_03_unbounded']

print("Running tests...")
success = True
for test_module in test_modules:
    test = importlib.import_module(test_module)
    try:
        test.run()
        print(f'- test "{test_module}":\t PASSED')
    except Exception as e:
        success = False
        print(f'- test "{test_module}":\t FAILED (message: {e})')

if success:
    print("Congratulations, your simplex algorithm seems to work correctly!")
else:
    print("Some of the tests failed. Fix your simplex implementation ASAP :)")

    