#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define CHESSBOARD_SIZE 8

vector<pair<int, int> > getNextMoves(int i, int j) {
    return {
        pair<int, int>(i - 2, j - 1),
        pair<int, int>(i - 2, j + 1),
        pair<int, int>(i + 2, j - 1),
        pair<int, int>(i + 2, j + 1),
        pair<int, int>(i - 1, j - 2),
        pair<int, int>(i + 1, j - 2),
        pair<int, int>(i - 1, j + 2),
        pair<int, int>(i + 1, j + 2)
    };
}

int findMinimumKnightMoves(pair<int, int> startPosition, pair<int, int> destinationPosition) {
    int i, j, nexti, nextj;
    pair<int, int> current;
    queue<pair<int, int> > queue;
    vector<int> distance(CHESSBOARD_SIZE * CHESSBOARD_SIZE, -1);
    queue.push(startPosition);
    distance[startPosition.first * CHESSBOARD_SIZE + startPosition.second] = 0;

    while (!queue.empty()) {
        current = queue.front();
        queue.pop();

        i = current.first;
        j = current.second;

        if (current == destinationPosition) {
            return distance[i * CHESSBOARD_SIZE + j];
        }

        for (pair<int, int> nextMove : getNextMoves(i, j)) {
            nexti = nextMove.first;
            nextj = nextMove.second;
            if (nexti >= 0 && nexti < CHESSBOARD_SIZE && nextj >= 0 && nextj < CHESSBOARD_SIZE && distance[nexti * CHESSBOARD_SIZE + nextj] == -1) {
                distance[nexti * CHESSBOARD_SIZE + nextj] = distance[i * CHESSBOARD_SIZE + j] + 1;
                queue.push(nextMove);
            }
        }
    }

    return 0;
}

pair<int, int> convertChessPositiontoPair(string position) {
    int i = CHESSBOARD_SIZE - atoi(&position[1]);
    int j = position[0] - 'a';

    return make_pair(i, j);
}

int main() {
    int t;
    string startPosition, endPosition;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> startPosition >> endPosition;
        cout << findMinimumKnightMoves(convertChessPositiontoPair(startPosition), convertChessPositiontoPair(endPosition)) << endl;
    }

    return 0;
}