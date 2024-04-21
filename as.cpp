#include "classes.h"

void matrix::improveHeuristc(vector<int> startingPos) {
    int distanceFromStarts;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            distanceFromStarts =
                sqrt(pow(startingPos[0] - j, 2) + pow(startingPos[1] - i, 2));
            blocks[i][j].heuristic =
                distanceFromStarts + blocks[i][j].heuristic;
        }
    }
}