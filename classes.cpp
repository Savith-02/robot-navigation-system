#include "classes.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

pair<int, int> matrix::updateBFSQueue(block nextBlock, queue<block> &que) {
    int returnValue;
    int x_coord = nextBlock.col;
    int y_coord = nextBlock.row;
    nodesTrversed++;
    // GotoUp
    // cout << "(" << nextBlock.row << ", " << nextBlock.col << ") -> ";
    if (y_coord - 1 >= 0 && (blocks[y_coord - 1][x_coord].color == "white" ||
                             blocks[y_coord - 1][x_coord].color == "green")) {
        blocks[y_coord - 1][x_coord].homePath = "down";
        if (blocks[y_coord - 1][x_coord].color == "green") {
            return pair(y_coord - 1, x_coord);
        }
        blocks[y_coord - 1][x_coord].color = "grey";
        que.push(blocks[y_coord - 1][x_coord]);
    }
    // GotoRight
    if (x_coord + 1 < cols && (blocks[y_coord][x_coord + 1].color == "white" ||
                               blocks[y_coord][x_coord + 1].color == "green")) {
        blocks[y_coord][x_coord + 1].homePath = "left";
        if (blocks[y_coord][x_coord + 1].color == "green") {
            return pair(y_coord, x_coord + 1);
        }
        blocks[y_coord][x_coord + 1].color = "grey";
        que.push(blocks[y_coord][x_coord + 1]);
    }
    // GotoDown
    if (y_coord + 1 < rows && (blocks[y_coord + 1][x_coord].color == "white" ||
                               blocks[y_coord + 1][x_coord].color == "green")) {
        blocks[y_coord + 1][x_coord].homePath = "up";
        if (blocks[y_coord + 1][x_coord].color == "green") {
            return pair(y_coord + 1, x_coord);
        }
        blocks[y_coord + 1][x_coord].color = "grey";
        que.push(blocks[y_coord + 1][x_coord]);
    }
    // GotoLeft
    if (x_coord - 1 >= 0 && (blocks[y_coord][x_coord - 1].color == "white" ||
                             blocks[y_coord][x_coord - 1].color == "green")) {
        blocks[y_coord][x_coord - 1].homePath = "right";
        if (blocks[y_coord][x_coord - 1].color == "green") {
            return pair(y_coord, x_coord - 1);
        }
        blocks[y_coord][x_coord - 1].color = "grey";
        que.push(blocks[y_coord][x_coord - 1]);
    }
    blocks[y_coord][x_coord].color = "black";
    // cout << endl;
    return pair(-1, -1);
}

matrix::matrix(int r, int c) : rows(r), cols(c) {
    // Allocate memory for rows
    blocks = new block *[rows];
    // Allocate memory for columns in each row
    for (int i = 0; i < rows; ++i) {
        blocks[i] = new block[cols];
    }
    int larger = max(rows, cols) - 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            blocks[i][j].row = i;
            blocks[i][j].col = j;
            blocks[i][j].color = "white";
            blocks[i][j].homePath = "";
            blocks[i][j].heuristic = larger;
        }
    }
}
void matrix::initHeuristics(vector<pair<int, int>> goalPositions) {
    int distance;
    for (int m = 0; m < goalPositions.size(); m++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                distance = sqrt(pow(goalPositions[m].first - j, 2) +
                                pow(goalPositions[m].second - i, 2));
                blocks[i][j].heuristic = min(distance, blocks[i][j].heuristic);
            }
        }
    }
}
int matrix::DFSmove(Cursor &cursor) {
    int returnValue;
    nodesTrversed++;
    // GotoUp
    // cout << "y: " << cursor.pos_y << ", x: " << cursor.pos_x << endl;
    if (cursor.pos_y - 1 >= 0 &&
        (blocks[cursor.pos_y - 1][cursor.pos_x].color == "white" ||
         blocks[cursor.pos_y - 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y - 1][cursor.pos_x].homePath = "down";
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
    // GotoDown
    else if (cursor.pos_y + 1 < rows &&
             (blocks[cursor.pos_y + 1][cursor.pos_x].color == "white" ||
              blocks[cursor.pos_y + 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y + 1][cursor.pos_x].homePath = "up";
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
pair<int, int> matrix::updateBSList(priority_queue<block> &list,
                                    block nextBlock) {
    nodesTrversed++;
    int returnValue;
    int x_coord = nextBlock.col;
    int y_coord = nextBlock.row;
    // GotoUp
    // cout << "(" << nextBlock.row << ", " << nextBlock.col << ") -> ";
    if (y_coord - 1 >= 0 && (blocks[y_coord - 1][x_coord].color == "white" ||
                             blocks[y_coord - 1][x_coord].color == "green")) {
        blocks[y_coord - 1][x_coord].homePath = "down";
        if (blocks[y_coord - 1][x_coord].color == "green") {
            return pair(y_coord - 1, x_coord);
        }
        blocks[y_coord - 1][x_coord].color = "grey";
        list.push(blocks[y_coord - 1][x_coord]);
    }
    // GotoRight
    if (x_coord + 1 < cols && (blocks[y_coord][x_coord + 1].color == "white" ||
                               blocks[y_coord][x_coord + 1].color == "green")) {
        blocks[y_coord][x_coord + 1].homePath = "left";
        if (blocks[y_coord][x_coord + 1].color == "green") {
            return pair(y_coord, x_coord + 1);
        }
        blocks[y_coord][x_coord + 1].color = "grey";
        list.push(blocks[y_coord][x_coord + 1]);
    }
    // GotoDown
    if (y_coord + 1 < rows && (blocks[y_coord + 1][x_coord].color == "white" ||
                               blocks[y_coord + 1][x_coord].color == "green")) {
        blocks[y_coord + 1][x_coord].homePath = "up";
        if (blocks[y_coord + 1][x_coord].color == "green") {
            return pair(y_coord + 1, x_coord);
        }
        blocks[y_coord + 1][x_coord].color = "grey";
        list.push(blocks[y_coord + 1][x_coord]);
    }
    // GotoLeft
    if (x_coord - 1 >= 0 && (blocks[y_coord][x_coord - 1].color == "white" ||
                             blocks[y_coord][x_coord - 1].color == "green")) {
        blocks[y_coord][x_coord - 1].homePath = "right";
        if (blocks[y_coord][x_coord - 1].color == "green") {
            return pair(y_coord, x_coord - 1);
        }
        blocks[y_coord][x_coord - 1].color = "grey";
        list.push(blocks[y_coord][x_coord - 1]);
    }
    blocks[y_coord][x_coord].color = "black";
    // cout << endl;
    return pair(-1, -1);
}
void matrix::getPath(Cursor &cursor, pair<int, int> &goal) {
    // cout << goal.second << goal.first << endl;
    Cursor backtracker({goal.second, goal.first});
    string direction;
    while (blocks[backtracker.pos_y][backtracker.pos_x].homePath != "") {
        direction = blocks[backtracker.pos_y][backtracker.pos_x].homePath;
        // cout << direction << endl;
        if (direction == "down") {
            cursor.path.insert(cursor.path.begin(), "up");
            backtracker.pos_y++;
        } else if (direction == "left") {
            cursor.path.insert(cursor.path.begin(), "right");
            backtracker.pos_x--;
        } else if (direction == "up") {
            cursor.path.insert(cursor.path.begin(), "down");
            backtracker.pos_y--;
        } else if (direction == "right") {
            cursor.path.insert(cursor.path.begin(), "left");
            backtracker.pos_x++;
        } else {
            cursor.path.insert(cursor.path.begin(), "error");
        }
    }
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
void matrix::printHeuristics() {
    cout << "\nHeuristics of blocks:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << blocks[i][j].heuristic << " ";
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

Cursor::Cursor(vector<int> start) {
    start_x = start[0];
    start_y = start[1];
    pos_x = start[0];
    pos_y = start[1];
}
void Cursor::printPath() {
    cout << "\n[";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "'" << path[i] << "'";
        if (i < path.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n" << endl;
}
void Cursor::backTrack(const matrix &Matrix) {
    string backTrackDirection = Matrix.blocks[pos_y][pos_x].homePath;
    // cout << "BackTracking" << endl;
    if (backTrackDirection == "down") {
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
