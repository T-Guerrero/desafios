#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<pair<int, int> > getNextCells(int i, int j) {
    return {
        pair<int, int>(i + 1, j),
        pair<int, int>(i - 1, j),
        pair<int, int>(i, j + 1),
        pair<int, int>(i, j - 1)
    };
}

pair<pair<int, int>, int> dfs(vector<bool>& visited, vector<string>& maze, int r, int c, int row, int col, int depth) {
    visited[row * c + col] = true;
    
    int i, j;
    pair<pair<int, int>, int> currentMaxDepth;
    pair<pair<int, int>, int> maxDepth(make_pair(row, col), depth);
    depth++;
    for (pair<int, int> nextCell : getNextCells(row, col)) {
        i = nextCell.first;
        j = nextCell.second;
        if(i >= 0 && i < r && j >= 0 && j < c && maze[i][j] == '.' && !visited[i * c + j]) {
            currentMaxDepth = dfs(visited, maze, r, c, i, j, depth);
            if (currentMaxDepth.second > maxDepth.second) {
                maxDepth = pair<pair<int, int>, int>(currentMaxDepth);
            }
        }
    }

    return maxDepth;
}

int getMaxRopeLength(vector<string>& maze, int r, int c) {
    int startRow = -1, startCol = -1;
    vector<bool> visited(r * c, false);
    pair<pair<int, int>, int> maxDepth;

    for (int i = 0; i < r && startRow == -1 && startCol == -1; i++) {
        for (int j = 0; j < c; j++) {
            if (maze[i][j] == '.') {
                startRow = i;
                startCol = j;
                break;
            }
        }
    }

    maxDepth = dfs(visited, maze, r, c, startRow, startCol, 0);

    visited.clear();
    visited.resize(r * c, false);

    startRow = maxDepth.first.first;
    startCol = maxDepth.first.second;
    maxDepth = dfs(visited, maze, r, c, startRow, startCol, 0);

    return maxDepth.second;
}

int main() {
    int t, r, c;
    string current;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> c >> r;

        vector<string> maze;
        for (int j = 0; j < r; j++) {
            cin >> current;
            maze.push_back(current);
        }

        cout << "Maximum rope length is " << getMaxRopeLength(maze, r, c) << "." << endl;
    }

    return 0;
}