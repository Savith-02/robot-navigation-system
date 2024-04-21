#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <queue>
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

  public:
    int heuristic; // BS
    int row;
    int col;
    string homePath;
    string color;
    pair<int, int> parent; // BS

    bool operator<(const block &other) const {
        return heuristic > other.heuristic; // Note: Min heap based on heuristic
    }
};
class List {};
class matrix {
  public:
    int rows;
    int cols;
    block **blocks; // Pointer to a pointer for dynamic memory allocation

    matrix(int r, int c);
    int DFSmove(Cursor &cursor);
    pair<int, int> updateBSList(priority_queue<block> &list, block nextBlock);
    void printColors();
    void initHeuristics(vector<pair<int, int>> goalPositions);
    void getPath(Cursor &cursor, pair<int, int> &goal);
    void printHeuristics();
    ~matrix();
};
#endif