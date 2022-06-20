from math import inf


class Node:
    def __init__(self, repr: str, pos: tuple, parent):
        self.pos = pos
        self.parent = parent
        self.repr = repr
        self.f = inf
        self.g = 0
        self.h = 0


class Grid:
    BLOCK = '#'
    SPACE = '.'
    START = '@'
    END = '$'
    PATH = '+'

    def __init__(self):
        self.width = 0
        self.height = 0
        self.nodes: Node = []
        
    def readfile(self, filename: str):
        with open(filename, 'r') as f:
            self.width = 0
            self.height = 0
            self.nodes.clear()

            for line in f.readlines():
                index = 0
                for ch in line:
                    if ch == self.BLOCK or ch == self.SPACE:
                        self.nodes.append(Node(ch, (index, self.height), None))
                        index += 1

                if self.width == 0:
                    self.width = index
                self.height += 1

    def find_path(self, start: tuple, end: tuple):
        start_node = Node(self.START, start, None)

        open_list = [start_node]
        closed_list = []

        while len(open_list) > 0:
            open_list = sorted(open_list, key=lambda k: k.f)

            current_node = open_list.pop(0)
            closed_list.append(current_node.pos)

            if current_node.pos == end:
                path = []
                current = current_node
                while current.pos != start:
                    path.append(current.pos)
                    current = current.parent
                return reversed(path)

            neighbours = [
                (current_node.pos[0] + 1, current_node.pos[1]), (current_node.pos[0] - 1, current_node.pos[1]),
                (current_node.pos[0], current_node.pos[1] + 1), (current_node.pos[0], current_node.pos[1] - 1),
                (current_node.pos[0] + 1, current_node.pos[1] + 1), (current_node.pos[0] + 1, current_node.pos[1] - 1),
                (current_node.pos[0] - 1, current_node.pos[1] + 1), (current_node.pos[0] - 1, current_node.pos[1] - 1)
            ]
            for pos in neighbours:
                if pos[0] < 0 or pos[1] < 0 or pos[0] >= self.width or pos[1] >= self.height:
                    continue
    
                node: Node = self.nodes[pos[0] + pos[1] * self.width]

                if node.repr == self.BLOCK:
                    continue

                if node.pos in closed_list:
                    continue

                start_dist = node.g + 1
                end_dist = (end[0] - node.pos[0]) ** 2 + (end[1] - node.pos[1]) ** 2
                total_cost = start_dist + end_dist

                if node.f > total_cost:
                    node.f = total_cost
                    node.g = start_dist
                    node.h = end_dist
                    node.parent = current_node

                    open_list.append(node)

    def find_and_save_path(self, filename: str, start: tuple, end: tuple):
        path = self.find_path(start, end)
        for node in path:
            self.nodes[node[0] + node[1] * self.width].repr = self.PATH
        self.nodes[start[0] + start[1] * self.width].repr = self.START
        self.nodes[end[0] + end[1] * self.width].repr = self.END

        with open(filename, 'w+') as f:
            text = ''
            for y in range(self.height):
                for x in range(self.width):
                    text += self.nodes[x + y * self.width].repr + ' '
                text += '\n'
            f.write(text)
