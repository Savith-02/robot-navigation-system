
# Robot Navigation Problem Solver
### This tool helps navigate a robot through a grid-based environment filled with obstacles to reach designated goal cells.

## What Does This Code Do?
This code provides solutions to the Robot Navigation problem using various tree-based search algorithms. The problem involves navigating a robot through an environment represented as a grid with walls, with the goal of reaching a "goal cell". 

## The code implements 6 popular search algorithms such as:
- depth-first search (DFS)
- breadth-first search (BFS)
- greedy best-first search (GBFS)
- A* search (AS)

and two custom search strategies 
- CUS1 - An optimised version of DFS: Cursor implements clockwise or anticlockwise search according to "goal cell" spread at initial state 
- CUS2 - An optimised version of GBFS: basically cursor can got to any direction

## How to Run It:
1. Clone the Repository: Clone this repository to your local machine using Git

2. Navigate to the Directory: Change your current directory to the repository directory

3. Compile source files using:
```
g++ main.cpp classes.cpp gbfs.cpp bfs.cpp dfs.cpp as.cpp cus1.cpp cus2.cpp
```

4. Select Search type {METHOD} and input file {INPUT-FILE} and run:
```
.\a.exe INPUT-FILE METHOD
```
METHOD can be either of the following: DFS, BFS, GBFS, AS, CUS1, CUS2
INPUT-FILE needs a file path

## What Is Outputted:
When a solution is found, the solver outputs the following information:

Filename: Name of the problem file.
Method: Search algorithm used.
Goal: The goal cell reached.
Number of Nodes: Total number of nodes created during the search.
Path: Sequence of moves from the initial configuration to the goal cell.

## Get Started:
Explore different problem configurations and search algorithms to efficiently navigate the robot to the goal cell. Happy navigating!
