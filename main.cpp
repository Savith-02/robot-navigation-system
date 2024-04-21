#include "classes.h"
#include "functions.cpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <tuple>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
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
    Matrix.printColors();                  // Prints the grid

    // while (cursor.atGreen == false) { // DFS
    //     switch (Matrix.DFSmove(cursor)) {
    //     case 0:
    //         cursor.path.push_back("top");
    //         break;
    //     case 1:
    //         cursor.path.push_back("right");
    //         break;
    //     case 2:
    //         cursor.path.push_back("bottom");
    //         break;
    //     case 3:
    //         cursor.path.push_back("left");
    //         break;
    //     case 4:
    //         cursor.path.pop_back();
    //         cursor.backTrack(Matrix);
    //     }
    // }
    // cursor.printPath();
    // cursor.cursorReset();

    priority_queue<block> blockList;
    block nextBlock;
    blockList.push(Matrix.blocks[cursor.pos_y][cursor.pos_x]);
    while (cursor.atGreen == false && !blockList.empty()) { // Best First
        nextBlock = blockList.top();
        blockList.pop();
        Matrix.updateBSList(blockList);
    }
    return 0;
}