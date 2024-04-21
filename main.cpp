#include "classes.h"
#include "functions.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

int main() {
    // Input dimensions
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

    vector<tuple<int, int, int, int>> walls;
    while (getline(inputFile, line)) {
        walls.push_back(parseLine(line));
    }
    // printWalls(walls);
    inputFile.close();

    matrix Matrix(gridSize[0], gridSize[1]);
    Matrix.blocks[startingPos[1]][startingPos[0]].color = "red";

    Cursor cursor;
    cursor.pos_x = startingPos[0];
    cursor.pos_y = startingPos[1];
    markBlockGoals(Matrix, goalPositions);
    markWalls(Matrix, walls);
    Matrix.printColors();

    while (cursor.atGreen == false) {
        switch (Matrix.move(cursor)) {
        case 0:
            cursor.path.push_back("top");
            break;
        case 1:
            cursor.path.push_back("right");
            break;
        case 2:
            cursor.path.push_back("bottom");
            break;
        case 3:
            cursor.path.push_back("left");
            break;
        case 4:
            cursor.path.pop_back();
            cursor.backTrack(Matrix);
            cursor.atGreen = true;
        }
    }
    cursor.printPath();
    return 0;
}