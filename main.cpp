#include "classes.h"
#include "functions.cpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <tuple>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is correct
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <filename> <method>" << endl;
        return 1; // Exit with error
    }
    string filename = argv[1];
    string method = argv[2];

    // Use the stored values
    // cout << "\nFilename: " << filename << " Method: " << method << endl;
    cout << filename << " " << method << endl;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }
    string line;
    // Parse the grid size
    getline(inputFile, line);
    vector<int> gridSize = parseIntegers(line);

    // Parse the starting position
    getline(inputFile, line);
    vector<int> startingPos = parseIntegers(line);
    // printData(gridSize, startingPos);

    // Parse the goal positions
    getline(inputFile, line);
    vector<pair<int, int>> goalPositions = parseGoalPos(line);
    // printGoals(goalPositions);

    // Parse the walls
    vector<tuple<int, int, int, int>> walls;
    while (getline(inputFile, line)) {
        walls.push_back(parseLine(line));
    }
    // printWalls(walls);
    inputFile.close();

    matrix Matrix(gridSize[0], gridSize[1]); // Initialize grid
    Matrix.blocks[startingPos[1]][startingPos[0]].color = "red";

    Cursor cursor(startingPos); // Initialise the position tracker

    markBlockGoals(Matrix, goalPositions); // Mark the greens
    markWalls(Matrix, walls);              // Mark the walls
    // Matrix.printColors();                  // Prints the grid
    pair<int, int> endGoal; // Store the goal reached

    if (method == "DFS") {

        while (cursor.atGreen == false) { // DFS
            switch (Matrix.DFSmove(cursor)) {
            case 0:
                cursor.path.push_back("up");
                break;
            case 1:
                cursor.path.push_back("right");
                break;
            case 2:
                cursor.path.push_back("down");
                break;
            case 3:
                cursor.path.push_back("left");
                break;
            case 4:
                cursor.path.pop_back();
                cursor.backTrack(Matrix);
            }
        }
        endGoal = pair(cursor.pos_y, cursor.pos_x);
    }
    // cursor.printPath();
    else if (method == "GBFS") {

        Matrix.initHeuristics(goalPositions);
        // Matrix.printHeuristics();
        priority_queue<block> blockList;
        block nextBlock;
        Matrix.blocks[cursor.pos_y][cursor.pos_x].color = "grey";
        blockList.push(Matrix.blocks[cursor.pos_y][cursor.pos_x]);

        while (cursor.atGreen == false && !blockList.empty()) { // Best First
            nextBlock = blockList.top();
            blockList.pop();
            endGoal = Matrix.updateBSList(blockList, nextBlock);
            if (endGoal != pair(-1, -1)) {
                cursor.atGreen = true;
                Matrix.getPath(cursor, endGoal);
            }
        }
    } else if (method == "BFS") {

        queue<block> que;
        block nextBlock;
        Matrix.blocks[cursor.pos_y][cursor.pos_x].color = "grey";
        que.push(Matrix.blocks[cursor.pos_y][cursor.pos_x]);

        while (cursor.atGreen == false && !que.empty()) {
            nextBlock = que.front();
            que.pop();
            endGoal = Matrix.updateBFSQueue(nextBlock, que);
            if (endGoal != pair(-1, -1)) {
                cursor.atGreen = true;
                Matrix.getPath(cursor, endGoal);
            }
        }
    } else {

        cout << "Invalid method";
        return 1;
    }
    cout << "<Node (" << endGoal.second << ", " << endGoal.first << ")> ";
    cout << Matrix.nodesTrversed;
    cursor.printPath();
    return 0;
}