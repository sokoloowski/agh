from __future__ import annotations
from dataclasses import dataclass
from typing import Dict, FrozenSet
import os


class Task:
    '''
    Class representing a single task in the project.

    Attributes:
    ----------
    name: str
        name of the task
    duration: int
        duration of the task
    direct_deps: FrozenSet[str]
        names of the tasks that have to be finished before the task can be performed
    all_deps: FrozenSet[str]
        names of all the tasks that have to be finished before the task, includes dependencies of the task's dependencies, their dependencies and so on
    direct_successors: FrozenSet[str]
        names of all the tasks in the project that depend directly on the task
    is_goal: bool
        true if the task is not a dependency of any other task
    is_dummy: bool
        true if the task is a dummy task, created just to build a proper project network

    Methods:
    --------
    __init__(name: str, duration: int, deps: FrozenSet[str], all_deps: FrozenSet[str] = None, direct_successors: FrozenSet[str] = None, is_dummy: bool = False)
        builds a tasks object
    precalculate_all_deps(project: Project):
        used to find all dependencies of the task, shouldn't be used outside the project constructor
    precalculate_successors(project: Project):
        used to find all successors of the task, shouldn't be used outside the project constructor

    Static Methods:
    ---------------
    dummy_task() -> Task
        creates a dummy task, useful when one has to build a project network
    '''
    name: str
    duration: int
    direct_deps: FrozenSet[str]
    all_deps: FrozenSet[str]
    direct_successors: FrozenSet[str]
    is_goal: bool
    is_dummy: bool

    def __init__(self,
                 name: str,
                 duration: int,
                 deps: FrozenSet[str],
                 all_deps: FrozenSet[str] = None,
                 direct_successors: FrozenSet[str] = None,
                 is_dummy: bool = False):
        self.name = name
        self.duration = duration
        self.direct_deps = deps
        self.all_deps = all_deps
        self.direct_successors = direct_successors
        self.is_dummy = is_dummy

    def precalculate_all_deps(self, project: Project):
        if self.all_deps is not None:
            return
        task_dependencies = [project.tasks[d] for d in self.direct_deps]
        for t in task_dependencies:
            t.precalculate_all_deps(project)
        self.all_deps = self.direct_deps.union(*[t.all_deps for t in task_dependencies])

    def precalculate_successors(self, project: Project):
        self.direct_successors = frozenset([t for t in project.tasks.values() if self.name in t.direct_deps])
        self.is_goal = len(self.direct_successors) == 0

    @staticmethod
    def dummy_task() -> Task:
        return Task("*", 0, frozenset(), frozenset(), frozenset(), is_dummy=True)


@dataclass
class Project:
    '''
    Class representing a project composed of tasks with given durations and dependencies.

    Attributes:
    -----------
    name: str
        name of the project
    tasks: Dict[str, Task]
        a dictionary mapping task names to the tasks themselves

    Static Methods:
    --------------
    from_file(path: str) -> Project:
        builds a project from a path at the give filepath
        the project format is as follows:
        - lines starting with # are comments
        - every other line corresponds to a single task and should be formatted as follows:
            <task name> <task duration> <task direct dependencies>
          whitespaces are significant!
    '''
    name: str
    tasks: Dict[str, Task]

    @staticmethod
    def from_file(path: str) -> Project:
        name = os.path.splitext(os.path.basename(path))[0]
        tasks = dict()

        with open(path) as f:
            for task_row in f.readlines():
                if task_row.startswith("#"):
                    continue
                task_components = task_row.split()
                task_name = task_components[0]
                task_duration = int(task_components[1])
                task_dependencies = frozenset(task_components[2:])
                task = Task(task_name, task_duration, task_dependencies)
                tasks[task_name] = task
        project = Project(name, tasks)
        for t in tasks.values():
            t.precalculate_all_deps(project)
            t.precalculate_successors(project)
        return project
