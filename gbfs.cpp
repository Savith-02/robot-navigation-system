#include "classes.h"
#include <cmath>

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
void matrix::printHeuristics() {
    cout << "\nHeuristics of blocks:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << blocks[i][j].heuristic << " ";
        }
        cout << endl;
    }
}