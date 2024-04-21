#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class matrix;
class Cursor {
  public:
    int pos_x;
    int pos_y;
    vector<string> path;
    bool atGreen = false;
    void printPath();
    void printCoordinates();
    void backTrack(const matrix &Matrix);
};
class block {
  public:
    string homePath;
    string color;
};
class matrix {
  public:
    int rows;
    int cols;
    block **blocks; // Pointer to a pointer for dynamic memory allocation

    matrix(int r, int c);
    int move(Cursor &cursor);
    void printColors();
    ~matrix();
};
#endif