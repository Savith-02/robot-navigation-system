#include "classes.h"

int matrix::DFSmoveAntiClockwise(Cursor &cursor) {
    int returnValue;
    nodesTrversed++;
    // cout << "y: " << cursor.pos_y << ", x: " << cursor.pos_x << endl;
    // GotoUp
    if (cursor.pos_y - 1 >= 0 &&
        (blocks[cursor.pos_y - 1][cursor.pos_x].color == "white" ||
         blocks[cursor.pos_y - 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y - 1][cursor.pos_x].homePath = "down";
        cursor.pos_y--;
        returnValue = 0;
    }
    // GotoLeft
    else if (cursor.pos_x - 1 >= 0 &&
             (blocks[cursor.pos_y][cursor.pos_x - 1].color == "white" ||
              blocks[cursor.pos_y][cursor.pos_x - 1].color == "green")) {
        blocks[cursor.pos_y][cursor.pos_x - 1].homePath = "right";
        cursor.pos_x--;
        returnValue = 3;
    }
    // GotoDown
    else if (cursor.pos_y + 1 < rows &&
             (blocks[cursor.pos_y + 1][cursor.pos_x].color == "white" ||
              blocks[cursor.pos_y + 1][cursor.pos_x].color == "green")) {
        blocks[cursor.pos_y + 1][cursor.pos_x].homePath = "up";
        cursor.pos_y++;
        returnValue = 2;
    }
    // GotoRight
    else if (cursor.pos_x + 1 < cols &&
             (blocks[cursor.pos_y][cursor.pos_x + 1].color == "white" ||
              blocks[cursor.pos_y][cursor.pos_x + 1].color == "green")) {
        blocks[cursor.pos_y][cursor.pos_x + 1].homePath = "left";
        cursor.pos_x++;
        returnValue = 1;
    }
    // BackTrack
    else {
        returnValue = 4;
    }

    if (blocks[cursor.pos_y][cursor.pos_x].color == "green") {
        cursor.atGreen = true; // Signal the finish
    } else {
        blocks[cursor.pos_y][cursor.pos_x].color = "black";
    }
    return returnValue;
}