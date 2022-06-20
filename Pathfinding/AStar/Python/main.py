from math import inf


class Node:
    def __init__(self, pos: tuple, parent):
        self.pos = pos
        self.parent = parent
        self.f = inf
        self.g = 0
        self.h = 0


def readfile(filename: str):
    with open(filename, 'r') as f:
        return f.read()


def find_path(start: tuple, end: tuple):
    start_node = Node(start, None)

    open_list = [start_node]
    closed_list = []

    while len(open_list) > 0:
        open_list = sorted(open_list, key=lambda k: k.f)

        current_node = open_list.pop(0)
        closed_list.append(current_node)

        if current_node.pos == end:
            return

        neighbours = [
            (current_node.pos[0] + 1, current_node.pos[1]), (current_node.pos[0] - 1, current_node.pos[1]),
            (current_node.pos[0], current_node.pos[1] + 1), (current_node.pos[0], current_node.pos[1] - 1),
            (current_node.pos[0] + 1, current_node.pos[1] + 1), (current_node.pos[0] + 1, current_node.pos[1] - 1),
            (current_node.pos[0] - 1, current_node.pos[1] + 1), (current_node.pos[0] - 1, current_node.pos[1] - 1)
        ]
        for pos in neighbours:
            pass
    

def main():
    find_path((0, 0), (9, 9))


if __name__ == '__main__':
    main()
