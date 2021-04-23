import networkx as nx
from ..model import Project
from ..project_network import ProjectState, ProjectNetwork
from typing import List, Dict
from ..solution import FullSolution


class Solver:
    '''
    A "critical path method" solver for the given project.

        Attributes:
    ----------
    project_network: ProjectNetwork
        a project network related to the given project

    Methods:
    --------
    __init__(problem: Project):
        create a solver for the given project
    solve -> FullSolution:
        solves the problem and returns the full solution
    forward_propagation() -> Dict[ProjectState,int]:
        calculates the earliest times the given events (project states) can occur
        returns a dictionary mapping network nodes to the timestamps
    backward_propagation(earliest_times: Dict[ProjectState, int]) -> Dict[ProjectState,int]:
        calculates the latest times the given events (project states) can occur
        uses earliest times to start the computation
        returns a dictionary mapping network nodes to the timestamps
    calculate_slacks(earliest_times: Dict[ProjectState, int], latest_times: Dict[ProjectState,int]) -> Dict[str, int]:
        calculates slacks for every task in the project
        uses earliest times and latest time of the events in the computations
        returns a dictionary mapping tasks names to their slacks
    create_critical_paths(slacks: Dict[str,int]) -> List[List[str]]:
        finds all the critical paths in the project based on the tasks' slacks
        returns list containing paths, every path is a list of tasks names put in the order they occur in the critical path 
    '''
    def __init__(self, problem: Project):
        self.project_network = ProjectNetwork(problem)

    def solve(self) -> FullSolution:
        earliest_times = self.forward_propagation()
        latest_times = self.backward_propagation(earliest_times)
        task_slacks = self.calculate_slacks(earliest_times, latest_times)
        critical_paths = self.create_critical_paths(task_slacks)
        # TODO:
        # set duration of the project based on the gathered data
        duration = earliest_times[self.project_network.goal_node]
        return FullSolution(duration, critical_paths, task_slacks)

    def forward_propagation(self) -> Dict[ProjectState, int]:
        # TODO:
        # earliest time of the project start node is always 0
        # every other event can occur as soon as all its predecessors plus duration of the tasks leading to the state
        #
        # earliest_times[state] = e
        earliest_times = {}
        earliest_times[self.project_network.start_node] = 0
        for start_node, end_node, task in self.project_network.edges():
            try:
                earliest_times[end_node] = max(earliest_times[end_node], earliest_times[start_node] + task.duration)
            except KeyError:
                earliest_times[end_node] = earliest_times[start_node] + task.duration
        # print(earliest_times)
        return earliest_times

    def backward_propagation(self, earliest_times: Dict[ProjectState, int]) -> Dict[ProjectState, int]:
        # TODO:
        # latest time of the project goal node always equals earliest time of the same node
        # every other event occur has to occur before its successors latest time
        latest_times = {}
        latest_times[self.project_network.goal_node] = earliest_times[self.project_network.goal_node]
        for start_node, end_node, task in self.project_network.edges()[::-1]:
            try:
                latest_times[start_node] = min(latest_times[start_node], latest_times[end_node] - task.duration)
            except KeyError:
                latest_times[start_node] = latest_times[end_node] - task.duration
        # print(latest_times)
        return latest_times

    def calculate_slacks(self, 
                         earliest_times: Dict[ProjectState, int], 
                         latest_times: Dict[ProjectState, int]) -> Dict[str, int]:
        # TODO:
        # slack of the task equals "the latest time of its end" minus "earliest time of its start" minus its duration
        # tip: remember to ignore dummy tasks (task.is_dummy could be helpful)
        slacks = {}
        for start_node, end_node, task in self.project_network.edges():
            if not task.is_dummy:
                slacks[task.name] = latest_times[end_node] - earliest_times[start_node] - task.duration
        # print(slacks)
        return slacks

    def create_critical_paths(self, slacks: Dict[str, int]) -> List[List[str]]:
        # TODO:
        # critical path start connects start node to the goal node
        # and uses only critical tasks (critical task has slack equal 0)
        # 1. create copy of the project network
        # 2. remove all the not critical tasks from the copy
        # 3. find all the paths from the start node to the goal node
        # 4. translate paths (list of nodes) to list of tasks connecting the nodes
        #
        # tip 2. use method "remove_edge(<start>, <end>" directly on the graph object 
        #        (e.g. self.project_network.network or rather its copy)
        # tip 3. nx.all_simple_paths method finds all the paths in the graph
        # tip 4. if "L" is a list "[1,2,3,4]", zip(L, L[1:]) will return [(1,2),(2,3),(3,4)]
        critical_paths = []
        project_network = self.project_network.network.copy()
        for start_node, end_node, task in self.project_network.edges():
            if not task.is_dummy:
                if slacks[task.name] != 0:
                    project_network.remove_edge(start_node, end_node)
        self.project_network.network = project_network
        for path in nx.all_simple_paths(project_network, self.project_network.start_node, self.project_network.goal_node):
            fixed_path = []
            for z in zip(path, path[1:]):
                for start_node, end_node, task in self.project_network.edges():
                    if z[0] == start_node and z[1] == end_node and not task.is_dummy:
                        fixed_path.append(task.name)
            critical_paths.append(fixed_path)
        print(critical_paths)
        return critical_paths
