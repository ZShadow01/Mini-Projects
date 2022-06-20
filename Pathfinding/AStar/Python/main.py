import sys
from astar import Grid


def main():
    if len(sys.argv) < 4:
        return

    try:
        start = tuple(map(int, sys.argv[1].split(',')))
        end = tuple(map(int, sys.argv[2].split(',')))
    except ValueError:
        return

    file_name = sys.argv[3]
    grid = Grid()
    grid.readfile(file_name)
    grid.find_and_save_path('path-result.txt', start, end)


if __name__ == '__main__':
    main()
