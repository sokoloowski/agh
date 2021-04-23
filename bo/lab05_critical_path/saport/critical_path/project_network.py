from __future__ import annotations
from dataclasses import dataclass
from typing import Dict, FrozenSet, Tuple, List
import networkx as nx
from networkx.drawing.nx_agraph import to_agraph
from .model import Task, Project


@dataclass(eq=True, frozen=True)
class ProjectState:
    '''
    Class representing a state of the project / node in the project network.

    Attributes:
    -----------
    index: int
        unique index of the state
    done: FrozenSet[str]
        set containing names of all the tasks completed at the state
    '''
    index: int
    done: FrozenSet[str]


class ProjectNetwork:
    '''
    Class representing a project network consisting of 
    nodes representing various states of the project completion
    and edges representing various tasks.

    Attributes:
    -----------
    project: Project
        project corresponding the network
    network: nx.DiGraph
        directed graph directly representing the network
    start_done: ProjectState
        an initial node in the network (empty state, nothing done)
    goal_done: ProjectState
        a goal node in the network (full state, everything done)

    Methods:
    --------
    __init__(project: Project):
        builds a network based on the given project
    nodes() -> List[ProjectState]:
        returns list of all the nodes in the network
    normal_nodes() -> List[ProjectState]:
        returns list of all the nodes in the network, that are not goal or start state   
    edges() -> List[Tuple[ProjectState, ProjectState, Task]]:
        returns list of all the edges in the network
        every edge is a 3-tuple with element:
        - starting node of the edge
        - terminal node of the edge
        - task corresponding to the edge
    predecessors(node: ProjectState) -> List[ProjectState]:
        returns all the nodes with an outcoming edge ending at the given node
    successors(node: ProjectState) -> List[ProjectState]:
        returns all the nodes with an incoming edge starting at the given node
    arc_task(start: ProjectState, end: ProjectState) -> Task:
        returns a task corresponding to the edge starting at the given 'start' node
        and ending at the given 'end' node
    arc_duration(start: ProjectState, end: ProjectState) -> int:
        returns duration of the task corresponding the edge starting at the given 'start' node
        and ending at the given 'end' node
    create_network(project: Project):
        builds a project network corresponding the given project
        should be called only in the constructor
    draw(path: str = None):
        uses graphviz to draw the network in the png file at the given path
        if there is no path provided, it uses project name
    '''
    project: Project
    network: nx.DiGraph
    start_node: ProjectState
    goal_node: ProjectState

    def __init__(self, project: Project):
        self.project = project
        self.create_network(project)

    def nodes(self) -> List[ProjectState]:
        return list(self.network.nodes())

    def normal_nodes(self) -> List[ProjectState]:
        return [n for n in self.network.nodes() if n != self.start_node and n != self.goal_node]

    def edges(self) -> List[Tuple[ProjectState, ProjectState, Task]]:
        return [(e[0], e[1], e[2]["task"]) for e in self.network.edges(data=True)]

    def predecessors(self, node: ProjectState) -> List[ProjectState]:
        return self.network.predecessors(node)

    def successors(self, node: ProjectState) -> List[ProjectState]:
        return self.network.successors(node)

    def arc_task(self, start: ProjectState, end: ProjectState) -> Task:
        return self.network.edges[start, end]["task"]

    def arc_duration(self, start: ProjectState, end: ProjectState) -> int:
        return self.arc_task(start, end).duration

    def create_network(self, project: Project):
        network = nx.DiGraph()
        tasks = project.tasks.values()
        project_states = dict()

        def find_successor(t: Task) -> FrozenSet[str]:
            state_after = t.all_deps.union({t.name})
            possible_successors = [n for n in network.nodes() if state_after.issubset(n.done)]
            smallest_successor = sorted(possible_successors, key=lambda x: len(x.done))[0]
            return smallest_successor

        def label(state: ProjectState) -> str:
            return str(state.index) + ".{" + ",".join(sorted(state.done)) + "}"

        def create_node(done: FrozenSet[str],
                        network: nx.DiGraph = network,
                        existing: Dict[FrozenSet[str], ProjectState] = project_states):
            try:
                return existing[done]
            except:
                state = ProjectState(len(network.nodes()) + 1, done)
                network.add_node(state, label=label(state))
                existing[done] = state
                return state

        def add_edge(s: ProjectState, e: ProjectState, task: Task, network: nx.DiGraph = network):
            network.add_edge(s, e, duration=task.duration, task=task, label=f"{task.name}.{task.duration}")

        def rename_nodes(network: nx.DiGraph, start_node: ProjectState,
                         goal_node: ProjectState) -> Tuple[nx.DiGraph, ProjectState, ProjectState]:
            new_network = nx.DiGraph()
            existing_states = dict()
            old_nodes = sorted(network.nodes(), key=lambda x: len(x.done))
            old_to_new = {n: create_node(n.done, new_network, existing_states) for n in old_nodes}
            for s, e in network.edges():
                task = network[s][e]["task"]
                add_edge(old_to_new[s], old_to_new[e], task, new_network)
            return new_network, old_to_new[start_node], old_to_new[goal_node]

        goal_states = frozenset([t.name for t in tasks])
        start_node = create_node(frozenset())
        for t in tasks:
            deps = t.all_deps
            create_node(deps)
        goal_node = create_node(goal_states)

        for t in tasks:
            add_edge(create_node(t.all_deps), find_successor(t), t)

        for t in tasks:
            if t.is_goal:
                add_edge(create_node(t.all_deps), goal_node, t)

        # Some algorithms enforce using dummy so every node has only single predecessor.
        # - https://criticalpathmethod.weebly.com/solved-problem.html
        # but it's not required for the basic critical path analysis
        #
        # for n in list(network.nodes()):
        #     preds = list(network.predecessors(n))
        #     if len(preds) > 1:
        #         for p in preds[1:]:
        #             t = network[p][n]["task"]
        #             network.remove_edge(p, n)
        #             d = create_node(p.done.union({t.name}))
        #             add_edge(p, d, t)
        #             add_edge(d, n, Task.dummy_task())

        # adds dummy edges to satisify dependencies at each node
        added_dummy_edge = True
        while added_dummy_edge:
            added_dummy_edge = False
            for n in sorted(network.nodes(), key=lambda x: len(x.done), reverse=True):
                all_successors = sorted(
                    [n1 for n1 in network.nodes() if n.done.issubset(n1.done) and len(n.done) < len(n1.done)],
                    key=lambda x: len(x.done))
                for s in all_successors:
                    if not nx.has_path(network, n, s):
                        add_edge(n, s, Task.dummy_task())
                        added_dummy_edge = True
                        break

        self.network, self.start_node, self.goal_node = rename_nodes(network, start_node, goal_node)

    def draw(self, path: str = None):
        output_path = f'{self.project.name}.png' if path is None else path
        agraph = to_agraph(self.network)
        agraph.layout('dot')
        agraph.draw(output_path)
