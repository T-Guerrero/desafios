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

void dfs(vector<bool>& visited, vector<string>& maze, int n, int m, int row, int col, int& k) {
    visited[row * m + col] = true;
    
    int i, j;
    for (pair<int, int> nextCell : getNextCells(row, col)) {
        i = nextCell.first;
        j = nextCell.second;
        if(i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == '.' && !visited[i * m + j]) {
            dfs(visited, maze, n, m, i, j, k);
        }
    }

    if (k > 0) {
        maze[row][col] = 'X';
        k--;
    }
}

int main() {
    int n, m ,k, startRow = -1, startCol = -1;

    cin >> n >> m >> k;

    vector<string> maze(n);
    for (int i = 0; i < n; i++) {
        cin >> maze[i];
    }

    for (int i = 0; i < n && startRow == -1 && startCol == -1; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '.') {
                startRow = i;
                startCol = j;
                break;
            }
        }
    }

    vector<bool> visited (n * m, false);
    dfs(visited, maze, n, m, startRow, startCol, k);

    for (int i = 0; i < n; i++) {
        cout << maze[i] << endl;
    }

    return 0;
}