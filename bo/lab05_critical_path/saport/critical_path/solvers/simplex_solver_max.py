from ..model import Project
from ..project_network import ProjectNetwork
from ...simplex.model import Model
from ...simplex.expressions.expression import Expression
from ..solution import BasicSolution


class Solver:
    '''
    Simplex based solver looking for the critical path in the project.
    Uses linear model maximizing length of the path in the project network. 

    Attributes:
    ----------
    project_network: ProjectNetwork
        a project network related to the given project
    model: simplex.model.Model
        a linear model looking for the maximal path in the project network
    Methods:
    --------
    __init__(problem: Project)
        create a solver for the given project
    create_simplex_model() -> simplex.model.Model
        builds a linear model of the problem
    solve() -> BasicSolution
        finds the duration of the critical (longest) path in the project network
    '''
    def __init__(self, problem: Project):
        self.project_network = ProjectNetwork(problem)
        self.model = self.create_simplex_model()

    def create_simplex_model(self) -> Model:
        # TODO:
        # 0) we need as many variables as there is edges in the project network
        # 1) every variable has to be <= 1
        # 2) sum of the variables starting at the initial state has to be equal 1
        # 3) sum of the variables ending at the goal state has to be equal 1
        # 4) for every other node, total flow going trough it has to be equal 0
        #    i.e. sum of incoming arcs minus sum of the outgoing arcs = 0
        # 5) we have to maximize length of the path
        #    (sum of variables weighted by the durations of the corresponding tasks)
        model = Model("critical path (max)")
        is_first_variable = True
        for start_node, end_node, task in self.project_network.edges():
            var = model.create_variable(f"x{start_node.index}{end_node.index}")
            model.add_constraint(var <= 1)
            if is_first_variable:
                objective = var * task.duration
                is_first_variable = False
            else:
                objective += var * task.duration

        model.maximize(objective)

        is_first_variable = True
        for variable in model.variables:
            if variable.name[1] == "1":
                if is_first_variable:
                    expr = variable
                    is_first_variable = False
                else:
                    expr += variable
        model.add_constraint(expr <= 1)
        model.constraints[-1].type = "="

        is_first_variable = True
        for variable in model.variables:
            if variable.name[2] == str(self.project_network.goal_node.index):
                if is_first_variable:
                    expr = variable
                    is_first_variable = False
                else:
                    expr += variable
        model.add_constraint(expr <= 1)
        model.constraints[-1].type = "="

        for node in self.project_network.normal_nodes():
            is_first_variable = True
            for variable in model.variables:
                if variable.name[2] == str(node.index):
                    if is_first_variable:
                        expr = variable
                        is_first_variable = False
                    else:
                        expr += variable
                if variable.name[1] == str(node.index):
                    if is_first_variable:
                        expr = -1 * variable
                        is_first_variable = False
                    else:
                        expr -= variable
            model.add_constraint(expr <= 0)
            model.constraints[-1].type = "="

        return model

    def solve(self) -> BasicSolution:
        solution = self.model.solve()
        return BasicSolution(int(solution.objective_value()))
