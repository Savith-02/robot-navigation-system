#ifndef CLASSES_H
#define CLASSES_H
#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class matrix;
class Cursor {
    int start_x;
    int start_y;

  public:
    int pos_y;
    int pos_x;
    bool atGreen = false;
    vector<string> path;
    Cursor(vector<int> start);
    void printPath();
    void printCoordinates();
    void backTrack(const matrix &Matrix);
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
    int nodesTrversed = 0;

    matrix(int r, int c);
    int DFSmove(Cursor &cursor);              // DFS
    int DFSmoveAntiClockwise(Cursor &cursor); // CUS1
    pair<int, int> updateBSList(priority_queue<block> &list, block nextBlock);
    pair<int, int> updateCUS2(priority_queue<block> &list, block nextBlock);
    void printColors();
    void initHeuristics(vector<pair<int, int>> goalPositions);
    void getPath(Cursor &cursor, pair<int, int> &goal);
    void getPathV2(Cursor &cursor, pair<int, int> &goal);
    void printHeuristics();
    pair<int, int> updateBFSQueue(block nextBlock, queue<block> &que);
    void improveHeuristc(vector<int> startingPos);

    ~matrix();
};
#endif