#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Cursor {
  public:
    int pos_x;
    int pos_y;
    vector<string> path;
    bool atGreen = false;
};
class block {
  public:
    int top;
    int right;
    int bottom;
    int left;
    string homePath;
    string color;
};
class matrix {
  public:
    int rows;
    int cols;
    string color;
    block **blocks; // Pointer to a pointer for dynamic memory allocation

    matrix(int r, int c) : rows(r), cols(c) {
        // Allocate memory for rows
        blocks = new block *[rows];
        // Allocate memory for columns in each row
        for (int i = 0; i < rows; ++i) {
            blocks[i] = new block[cols];
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                blocks[i][j].top = 0;
                blocks[i][j].left = 0;
                blocks[i][j].bottom = 0;
                blocks[i][j].right = 0;
                blocks[i][j].color = "white";
            }
        }
    }
    int getDirection(Cursor cursor) {
        if (blocks[cursor.pos_y - 1][cursor.pos_x].color == "white" &&
            cursor.pos_y - 1 >= 0) {
            return 0;
        } else if (blocks[cursor.pos_y][cursor.pos_x + 1].color == "white" &&
                   cursor.pos_x + 1 < cols) {
            return 1;
        } else if (blocks[cursor.pos_y + 1][cursor.pos_x].color == "white" &&
                   cursor.pos_y + 1 < rows) {
            return 2;
        } else if (blocks[cursor.pos_y][cursor.pos_x - 1].color == "white" &&
                   cursor.pos_x - 1 >= 0) {
            return 3;
        } else {
            return 4;
        }
    }
    void goTop(Cursor &cursor) {
    }
    void goRight(Cursor &cursor) {
    }
    void goBottom(Cursor &cursor) {
    }
    void goLeft(Cursor &cursor) {
    }
    void printColors() {
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

    ~matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] blocks[i];
        }
        delete[] blocks;
    }
};
#endif