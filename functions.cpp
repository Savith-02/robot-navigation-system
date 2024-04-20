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