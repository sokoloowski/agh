from __future__ import annotations
from dataclasses import dataclass
from typing import Dict, List


@dataclass
class BasicSolution:
    '''
    Class representing a basic solution to the critical path problem.
    Basic solution is just a duration of the criticial path.

    Attributes:
    -----------
    duration: int
        duration of the critical path 
    '''
    duration: int


@dataclass
class FullSolution:
    '''
    Class representing a full solution to the critical path problem.

    Attributes:
    -----------
    duration: int
        duration of the critical path 
    critical_paths: List[List[str]]
        list containing all critical paths in the problem
        every critical path is just a list of names of the tasks put in the correct order 
        [A, B, C] would represent a chain of tasks A -> B -> C.
    task_slacks: Dict[str, int]
        a dictionary mapping tasks' names to their total slacks

    Methods:
    --------
    serialize() -> str:
        serializes solution to a textual representation:
        <duration>;<1st critical path elements separated with spaces>|<2nd critical path....>|...;<task 1>:<slack of task 1> <task 2>:<slack of task 2> ...

    Static Methods:
    ---------------
    deserialize(text: str) -> FullSolution:
        builds a full solution from its textual representation
    expected_solution_from_file(path: str) -> FullSolution:
        looks for a comment line containing an serialized solution in the given project file
        if there is none it return None
        otherwise it deserializes the solution and returns it
    '''
    duration: int
    critical_paths: List[List[str]]
    task_slacks: Dict[str, int]

    def serialize(self) -> str:
        return f'''{self.duration};{"|".join([" ".join(cp) for cp in self.critical_paths])};{" ".join([f'{k}:{v}' for k,v in self.task_slacks.items()])}'''

    @staticmethod
    def deserialise(text: str) -> FullSolution:
        components = text.split(";")
        duration = int(components[0])
        critical_paths = [c.split() for c in components[1].split("|")]
        task_slacks = {x.split(":")[0]: int(x.split(":")[1]) for x in components[2].split()}
        return FullSolution(duration, critical_paths, task_slacks)

    @staticmethod
    def expected_solution_from_file(path: str) -> FullSolution:
        with open(path) as f:
            for task_row in f.readlines():
                if task_row.startswith("#"):
                    return FullSolution.deserialise(task_row[1:])
        return None
