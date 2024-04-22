#include "classes.h"

pair<int, int> matrix::updateCUS2(priority_queue<block> &list,
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
        // cout << "1";
    }
    // goTopRight
    if (y_coord - 1 >= 0 && x_coord + 1 < cols &&
        (blocks[y_coord - 1][x_coord + 1].color == "white" ||
         blocks[y_coord - 1][x_coord + 1].color == "green")) {
        blocks[y_coord - 1][x_coord + 1].homePath = "bottomLeft";
        if (blocks[y_coord - 1][x_coord + 1].color == "green") {
            return pair(y_coord - 1, x_coord + 1);
        }
        blocks[y_coord - 1][x_coord + 1].color = "grey";
        list.push(blocks[y_coord - 1][x_coord + 1]);
        // cout << "2";
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
        // cout << "3";
    }
    // GotoBottomRight
    if (x_coord + 1 < cols && y_coord + 1 < rows &&
        (blocks[y_coord + 1][x_coord + 1].color == "white" ||
         blocks[y_coord + 1][x_coord + 1].color == "green")) {
        blocks[y_coord + 1][x_coord + 1].homePath = "topLeft";
        if (blocks[y_coord + 1][x_coord + 1].color == "green") {
            return pair(y_coord + 1, x_coord + 1);
        }
        blocks[y_coord + 1][x_coord + 1].color = "grey";
        list.push(blocks[y_coord + 1][x_coord + 1]);
        // cout << "4";
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
        // cout << "5";
    }
    // GotoDownLeft
    if (y_coord + 1 < rows && x_coord - 1 >= 0 &&
        (blocks[y_coord + 1][x_coord - 1].color == "white" ||
         blocks[y_coord + 1][x_coord - 1].color == "green")) {
        blocks[y_coord + 1][x_coord - 1].homePath = "topRight";
        if (blocks[y_coord + 1][x_coord - 1].color == "green") {
            return pair(y_coord + 1, x_coord - 1);
        }
        blocks[y_coord + 1][x_coord - 1].color = "grey";
        list.push(blocks[y_coord + 1][x_coord - 1]);
        // cout << "6";
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
        // cout << "7";
    }
    // GotoTopLeft
    if (x_coord - 1 >= 0 && y_coord - 1 >= 0 &&
        (blocks[y_coord - 1][x_coord - 1].color == "white" ||
         blocks[y_coord - 1][x_coord - 1].color == "green")) {
        blocks[y_coord - 1][x_coord - 1].homePath = "bottomRight";
        if (blocks[y_coord - 1][x_coord - 1].color == "green") {
            return pair(y_coord - 1, x_coord - 1);
        }
        blocks[y_coord - 1][x_coord - 1].color = "grey";
        list.push(blocks[y_coord - 1][x_coord - 1]);
        // cout << "8";
    }
    blocks[y_coord][x_coord].color = "black";
    // cout << endl;
    return pair(-1, -1);
}
void matrix::getPathV2(Cursor &cursor, pair<int, int> &goal) {
    // cout << goal.second << goal.first << endl;
    Cursor backtracker({goal.second, goal.first});
    string direction;
    while (blocks[backtracker.pos_y][backtracker.pos_x].homePath != "") {
        direction = blocks[backtracker.pos_y][backtracker.pos_x].homePath;
        // cout << direction << endl;
        if (direction == "down") {
            cursor.path.insert(cursor.path.begin(), "up");
            backtracker.pos_y++;
        } else if (direction == "bottomLeft") {
            cursor.path.insert(cursor.path.begin(), "topRight");
            backtracker.pos_y++;
            backtracker.pos_x--;
        } else if (direction == "left") {
            cursor.path.insert(cursor.path.begin(), "right");
            backtracker.pos_x--;
        } else if (direction == "topLeft") {
            cursor.path.insert(cursor.path.begin(), "bottomRight");
            backtracker.pos_x--;
            backtracker.pos_y--;
        } else if (direction == "up") {
            cursor.path.insert(cursor.path.begin(), "down");
            backtracker.pos_y--;
        } else if (direction == "topRight") {
            cursor.path.insert(cursor.path.begin(), "bottomLeft");
            backtracker.pos_y--;
            backtracker.pos_x++;
        } else if (direction == "right") {
            cursor.path.insert(cursor.path.begin(), "left");
            backtracker.pos_x++;
        } else if (direction == "bottomRight") {
            cursor.path.insert(cursor.path.begin(), "topLeft");
            backtracker.pos_x++;
            backtracker.pos_y++;
        } else {
            cursor.path.insert(cursor.path.begin(), "error");
        }
    }
}