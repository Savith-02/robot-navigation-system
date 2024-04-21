#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class matrix;
class Cursor {
    int start_x; //
    int start_y; //

  public:
    int pos_y;
    int pos_x;
    bool atGreen = false;
    void cursorReset(); //
    vector<string> path;
    Cursor(vector<int> start); //
    void printPath();
    void printCoordinates();
    void backTrack(const matrix &Matrix); //
};
class block {
    int heuristic; //

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
    int DFSmove(Cursor &cursor);
    int bestFirstMove(); //
    void printColors();
    void setBlockeuristic();
    ~matrix();
};
#endif