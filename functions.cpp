#include "classes.h"
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<int> parseIntegers(const string &input) {
    vector<int> integers;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        integers.push_back(stoi(token));
    }
    return integers;
}
vector<pair<int, int>> parseGoalPos(const string &input) {
    stringstream ss(input);
    string token;
    vector<pair<int, int>> goalPositions;
    while (getline(ss, token, '|')) {
        vector<int> pos = parseIntegers(token);
        if (pos.size() == 2) {
            goalPositions.emplace_back(pos[0], pos[1]);
        }
    }
    return goalPositions;
}

tuple<int, int, int, int> parseLine(const string &line) {
    stringstream ss(line);
    int a, b, c, d;
    char comma;
    ss >> a >> comma >> b >> comma >> c >> comma >> d;
    return make_tuple(a, b, c, d);
}
void printGoals(const vector<pair<int, int>> &goalPositions) {
    for (const auto &pair : goalPositions) {
        std::cout << "(" << pair.first << ", " << pair.second << ")"
                  << std::endl;
    }
}

void printWalls(const vector<tuple<int, int, int, int>> &Walls) {
    cout << "Walls read from file:" << endl;
    for (const auto &tuple : Walls) {
        cout << "(" << get<0>(tuple) << ", " << get<1>(tuple) << ", "
             << get<2>(tuple) << ", " << get<3>(tuple) << ")" << endl;
    }
}
void printData(const vector<int> &gridSize, const vector<int> &startingPos) {
    cout << "Grid Size: " << gridSize[0] << " rows x " << gridSize[1]
         << " columns" << endl;
    cout << "Starting Position: (" << startingPos[0] << ", " << startingPos[1]
         << ")" << endl;
}
void markBlockGoals(matrix &Matrix,
                    const vector<pair<int, int>> &goalPositions) {
    for (const auto &pair : goalPositions) {
        Matrix.blocks[pair.second][pair.first].color = "green";
    }
}
void markWalls(matrix &Matrix, const vector<tuple<int, int, int, int>> &walls) {
    for (const auto &tuple : walls) {
        for (int i = get<1>(tuple); i < get<1>(tuple) + get<3>(tuple); i++) {
            for (int j = get<0>(tuple); j < get<0>(tuple) + get<2>(tuple);
                 j++) {
                Matrix.blocks[i][j].color = "black";
            }
        }
    }
}
int getNearestGoalX(const vector<pair<int, int>> &goalPositions) {
    // Initialize the minimum x-coordinate and its index with the first goal
    // position
    int min_x = goalPositions[0].first;

    // Iterate through the goal positions starting from the second one
    for (size_t i = 1; i < goalPositions.size(); ++i) {
        // If the current x-coordinate is lower than the minimum x-coordinate
        // encountered so far, update the minimum x-coordinate
        if (goalPositions[i].first < min_x) {
            min_x = goalPositions[i].first;
        }
    }

    return min_x;
}
int getFarthestGoalX(const vector<pair<int, int>> &goalPositions) {
    int max_x = goalPositions[0].first;

    // Iterate through the goal positions starting from the second one
    for (size_t i = 1; i < goalPositions.size(); ++i) {
        // If the current x-coordinate is higher than the maximum x-coordinate
        // encountered so far, update the maximum x-coordinate
        if (goalPositions[i].first > max_x) {
            max_x = goalPositions[i].first;
        }
    }
    return max_x;
}
string getBestOption(const vector<pair<int, int>> &goalPositions, int start_x) {
    int min_x = getNearestGoalX(goalPositions);
    int max_x = getNearestGoalX(goalPositions);

    if (min_x < start_x && max_x < start_x) {
        return "anitClockWise";
    } else {
        return "clockWise";
    }
}