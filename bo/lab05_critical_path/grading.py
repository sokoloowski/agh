import json

from typing import List

from _pytest.reports import Item
from _pytest.reports import TestReport
from _pytest.runner import CallInfo

from test_utils import RelativePathLoader

def pytest_addoption(parser):
    group = parser.getgroup("grading")
    group.addoption(
        "--points",
        action="store_true",
        dest="points",
        default=True,
        help="adds points summary to grading report",
    )
    group.addoption(
        "--teacher-dir",
        "--teacher",
        action="store",
        dest="teacher",
        default=None,
        help="passes a solution dir containing project that can to be used to grade assignments",
    )
    group.addoption(
        "--student-dir",
        "--student",
        action="store",
        dest="student",
        default=None,
        help="passes a student dir containing project that can to be used to grade assignments",
    )
    group.addoption(
        "--explain",
        action="store_true",
        dest="explain",
        default=True,
        help="adds detailed info about the failures in the grade report",
    )


def pytest_generate_tests(metafunc):
    student_value = metafunc.config.option.student
    teacher_value = metafunc.config.option.teacher
    if "student_loader" in metafunc.fixturenames and student_value is not None:
        module_loader = RelativePathLoader(student_value)
        metafunc.parametrize("student_loader", [module_loader])
    if "teacher_loader" in metafunc.fixturenames and teacher_value is not None:
        module_loader = RelativePathLoader(teacher_value)
        metafunc.parametrize("teacher_loader", [module_loader])
    if 'student_dir' in metafunc.fixturenames and student_value is not None:
        metafunc.parametrize("student_dir", [student_value])
    if 'teacher_dir' in metafunc.fixturenames and teacher_value is not None:
        metafunc.parametrize("teacher_dir", [teacher_value])


def pytest_configure(config):
    points = config.option.points
    explain = config.option.explain
    if points or explain:
        config._points = PointsReporter(points, explain)
        config.pluginmanager.register(config._points)


def pytest_unconfigure(config):
    points = getattr(config, "_points", None)
    if points:
        del config._points
        config.pluginmanager.unregister(points)


class PointsReporter:
    include_points: bool
    include_explanations: bool
    points: int
    total_points: int
    explanations: List[str]

    def __init__(self, include_points: bool, include_explanations: bool):
        self.include_points = include_points
        self.include_explanations = include_explanations
        self.points = 0
        self.total_points = 0
        self.explanations = []

    def pytest_runtest_makereport(self, item: Item, call: CallInfo):
        def get_points(report):
            points = [v for k, v in report.user_properties if k == "points"]
            return points[0] if points else 1

        result = TestReport.from_item_and_call(item, call)
        points = get_points(result)
        if result.when == "call":
            self.total_points += points
            if result.failed:
                msg = str(call.excinfo.getrepr(style="value"))
                self.explanations.append(msg)
            if result.passed:
                self.points += points

    def pytest_sessionfinish(self, session):
        report = dict()

        if self.include_points:
            report["points"] = self.points
            report["total"] = self.total_points
        if self.include_explanations:
            report["issues"] = self.explanations
        print(json.dumps(report))
