#include "classes.h"
#include <algorithm>

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

void Cursor::printCoordinates() {
    cout << "x: " << pos_x << ", "
         << "y: " << pos_y;
}
