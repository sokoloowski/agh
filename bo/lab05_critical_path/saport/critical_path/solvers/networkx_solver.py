import networkx as nx
from ..model import Project
from ..project_network import ProjectNetwork
from ..solution import BasicSolution


class Solver:
    '''
    Very basic networkx solver looking for the critical path in the project.
    Useful to use as a comparison with other solvers.

    Attributes:
    ----------
    project_network: ProjectNetwork
        a project network related to the given project

    Methods:
    --------
    __init__(problem: Project)
        create a solver for the given project
    solve() -> BasicSolution
        finds the duration of the critical (longest) path in the project network
    '''
    def __init__(self, problem: Project):
        self.project_network = ProjectNetwork(problem)

    def solve(self) -> BasicSolution:
        return BasicSolution(nx.algorithms.dag_longest_path_length(self.project_network.network, weight="duration"))
