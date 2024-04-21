#include "classes.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
Cursor::Cursor(vector<int> start) {
    start_x = start[0];
    start_y = start[1];
    pos_x = start[0];
    pos_y = start[1];
}
void Cursor::cursorReset() {
    pos_x = start_x;
    pos_y = start_y;
    atGreen = false;
}
matrix::matrix(int r, int c) : rows(r), cols(c) {
    // Allocate memory for rows
    blocks = new block *[rows];
    // Allocate memory for columns in each row
    for (int i = 0; i < rows; ++i) {
        blocks[i] = new block[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            blocks[i][j].color = "white";
        }
    }
}
int matrix::DFSmove(Cursor &cursor) {
    int returnValue;

    // GotoTop
    cout << "y: " << cursor.pos_y << ", x: " << cursor.pos_x << endl;
    if (cursor.pos_y - 1 >= 0 &&
        (blocks[cursor.pos_y - 1][cursor.pos_x].color == "white" ||
         blocks[cursor.pos_y - 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y - 1][cursor.pos_x].homePath = "bottom";
        cursor.pos_y--;
        returnValue = 0;
    }
    // GotoRight
    else if (cursor.pos_x + 1 < cols &&
             (blocks[cursor.pos_y][cursor.pos_x + 1].color == "white" ||
              blocks[cursor.pos_y][cursor.pos_x + 1].color == "green")) {
        blocks[cursor.pos_y][cursor.pos_x + 1].homePath = "left";
        cursor.pos_x++;
        returnValue = 1;
    }
    // GotoBottom
    else if (cursor.pos_y + 1 < rows &&
             (blocks[cursor.pos_y + 1][cursor.pos_x].color == "white" ||
              blocks[cursor.pos_y + 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y + 1][cursor.pos_x].homePath = "top";
        cursor.pos_y++;
        returnValue = 2;
    }
    // GotoLeft
    else if (cursor.pos_x - 1 >= 0 &&
             (blocks[cursor.pos_y][cursor.pos_x - 1].color == "white" ||
              blocks[cursor.pos_y][cursor.pos_x - 1].color == "green")) {
        blocks[cursor.pos_y][cursor.pos_x - 1].homePath = "right";
        cursor.pos_x--;
        returnValue = 3;
    }
    // BackTrack
    else {
        returnValue = 4;
    }

    if (blocks[cursor.pos_y][cursor.pos_x].color == "green") {
        cursor.atGreen = true; // Signal the finish
    } else {
        blocks[cursor.pos_y][cursor.pos_x].color = "black";
    }

    return returnValue;
}
void matrix::updateBSList(priority_queue<block> &list, block nextBlock) {
}
int matrix::bestFirstMove() {
    return 0;
}
void setBlockHeuristic() {
}

void matrix::printColors() {
    cout << "\nColors of blocks:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << blocks[i][j].color;
            if (blocks[i][j].color == "red") {
                cout << "   ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

matrix::~matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] blocks[i];
    }
    delete[] blocks;
}

void Cursor::printPath() {
    cout << "Path: ";
    for (const auto &str : path) {
        cout << str << " ";
    }
    cout << endl;
}
void Cursor::backTrack(const matrix &Matrix) {
    string backTrackDirection = Matrix.blocks[pos_y][pos_x].homePath;
    cout << "BackTracking" << endl;
    if (backTrackDirection == "bottom") {
        pos_y++;
    } else if (backTrackDirection == "left") {
        pos_x--;
    } else if (backTrackDirection == "right") {
        pos_x++;
    } else {
        pos_y--;
    }
}
void Cursor::printCoordinates() {
    cout << "x: " << pos_x << ", "
         << "y: " << pos_y;
}
