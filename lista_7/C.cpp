#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<pair<int, int> > getAdjacents(int i, int j) {
    return {
        pair<int, int>(i + 1, j),
        pair<int, int>(i - 1, j),
        pair<int, int>(i, j + 1),
        pair<int, int>(i, j - 1),
        pair<int, int>(i + 1, j + 1),
        pair<int, int>(i - 1, j + 1),
        pair<int, int>(i + 1, j - 1),
        pair<int, int>(i - 1, j - 1)
    };
}

bool isConsecutive(char currentLetter, char newLetter) {
    return newLetter - currentLetter == 1;
}

int findLongestPathOfConsecutiveLetters(vector<string>& grid, int height, int width) {
    int row, col, nextRow, nextCol, newDistance, longestPathOfConsecutiveLetters = 0;
    vector<int> distance(height * width, 0);
    queue<pair<int, int> > queue;
    pair<int, int> current;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == 'A') {
                distance[i * width + j] = 1;
                queue.push(make_pair(i, j));
            }
        }
    }

    while(!queue.empty()) {
        current = queue.front();
        queue.pop();

        row = current.first;
        col = current.second;

        longestPathOfConsecutiveLetters = max(longestPathOfConsecutiveLetters, distance[row * width + col]);
        newDistance = distance[row * width + col] + 1;
        for (pair<int, int> adjacent : getAdjacents(row, col)) {
            nextRow = adjacent.first;
            nextCol = adjacent.second;
            if (nextRow >= 0 && nextRow < height && nextCol >= 0 && nextCol < width) {
                if (isConsecutive(grid[row][col], grid[nextRow][nextCol]) && newDistance > distance[nextRow * width + nextCol]) {
                    distance[nextRow * width + nextCol] = newDistance;
                    queue.push(adjacent);
                }
            }
        }
    }

    return longestPathOfConsecutiveLetters;
}

int main() {
    int h, w;
    string current;

    cin >> h >> w;

    for(int count = 1; h > 0 && w > 0; count++) {
        vector<string> grid;
        for (int i = 0; i < h; i++) {
            cin >> current;
            grid.push_back(current);
        }

        cout << "Case " << count << ": " << findLongestPathOfConsecutiveLetters(grid, h, w) << endl;
        cin >> h >> w;
    }

    return 0;
}