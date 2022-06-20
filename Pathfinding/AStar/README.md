# Pathfinding - A* algorithm

README - not done yet

## C++ implementation - How to use
Note that the **MingW** C/C++ compiler is required to compile the C++ code

### Build & Compilation
Go to the directory where the *.cpp and *.h files are located and enter the following line to the terminal:

```
g++ main.cpp Grid.cpp Vector.cpp Node.cpp -o astar
```

This should create the executable file under the name `astar`

### Usage
Open the terminal under the directory where the executable file is located.

There are 3 required arguments in order to run the program successfully.

```
      Start  End  map file path
astar [x,y] [x,y] [file path]
```

On success, the program will create a text file "path-result.txt" in which the map with a starting point, end point the shortest path is given. If it fails, nothing changes.

#### Map format
The map has to be correctly formatted for the program to work.

Example map:
```
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
# # # # # # # # # .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
```

If the widths are not consistent (equal), the program will fail. Furthermore, the map has to consist of only `.` and `#` which represent an empty space and a blocked, impassable space.
