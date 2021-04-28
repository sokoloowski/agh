from __future__ import annotations
from dataclasses import dataclass
from typing import List


@dataclass
class Item:
    """
    A dataclass representing an item in the knapsack problem.

    Attributes
    ----------
    index : int
        unique index of the item
    value : int
        how much is the item worth
    weight : int
        how much does the item weight
    """
    index: int
    value: int
    weight: int

    def __str__(self):
        return f'{self.index}(v:{self.value}, w:{self.weight})'


@dataclass
class Solution:
    """
    A dataclass representing a solution to the knapsack problem.

    Attributes
    ----------
    items : List[item]
        list of the items taken in the solution
    value : int
        how much is the knapsack worth
    weight : int
        how much does the knapsack weight
    optimal : bool
        whether the solution was proven to be optimal

    Static Methods
    --------------
    from_items(items: List[Item], optimal: bool = False) -> Solution
        creates a solution given the list of items to take and whether the solution is optimal
    empty() -> Solution
        creates a solution without any items

    Methods
    -------
    with_added_item(item: Item) -> Solution:
        creates a new solution based on the current one with only one item added
    """
    items: List[Item]
    value: int
    weight: int
    optimal: bool

    @staticmethod
    def from_items(items: List[Item], optimal: bool = False) -> Solution:
        value = sum([i.value for i in items])
        weight = sum([i.weight for i in items])
        return Solution(items, value, weight, optimal)

    @staticmethod
    def empty() -> Solution:
        return Solution([], 0, 0, False)

    def with_added_item(self, item) -> Solution:
        return Solution(self.items + [item], self.value + item.value, self.weight + item.weight, False)

    def __str__(self):
        text_representation = f'* total value: {self.value}\n* optimal: {self.optimal}\n* total weight: {self.weight}\n* items:\n'
        for item in self.items:
            text_representation += f'  - {item}\n'
        return text_representation


@dataclass
class Problem:
    """
    A dataclass representing a knapsack problem.

    Attributes
    ----------
    items : List[item]
        list of the items in the problem
    capacity : int
        what is the maximum weight of the knapsack 

    Static Methods
    --------------
    from_path(path: str) -> Problem
        creates a solution based on the text representation in a file at the given path
    """
    items: List[Item]
    capacity: int

    @staticmethod
    def from_path(path: str) -> Problem:
        with open(path) as f:
            header = list(map(int, f.readline().split()))
            n_items = header[0]
            capacity = header[1]
            items: List[Item] = []
            for i in range(n_items):
                item_row = list(map(int, f.readline().split()))
                value = item_row[0]
                weight = item_row[1]
                items.append(Item(index=i, value=value, weight=weight))
            return Problem(items=items, capacity=capacity)