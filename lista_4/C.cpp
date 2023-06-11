#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007

int calculateNumberOfPaths(vector<int>& subResult, vector<string>& grid, int i, int j, int n) {
    if (i >= n || j >= n || grid[i][j] == '*') {
        return 0;
    }

    if (i == n - 1 && j == n - 1) {
        return 1;
    }

    if (subResult[i*n + j] == -1) {
        subResult[i*n + j] = (calculateNumberOfPaths(subResult, grid, i + 1, j, n)
                            + calculateNumberOfPaths(subResult, grid, i, j + 1, n)) % MOD;
    }

    return subResult[i*n + j];
}

int main() {
    int n;
    vector<string> grid;
    string currentLine;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> currentLine;
        grid.push_back(currentLine);
    }

    vector <int> subResult(n*n, -1);
    cout << calculateNumberOfPaths(subResult, grid, 0, 0, n) << endl;

    return 0;
}