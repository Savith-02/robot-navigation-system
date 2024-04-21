#include "classes.h"

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
