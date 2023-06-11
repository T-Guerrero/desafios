#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007

int countMaxPaths(vector<vector<long long> >& paths, int n, int k, int d, int weight, int passedThroughAtLeastD) {
    if (weight == n && passedThroughAtLeastD) {
        return 1;
    }

    if (weight > n) {
        return 0;
    }

    if (paths[weight][passedThroughAtLeastD] != -1) {
        return paths[weight][passedThroughAtLeastD];
    }

    long long maxPaths = 0;
    for (int i = 1; i <= k; i++) {
        maxPaths += countMaxPaths(paths, n, k, d, weight + i, passedThroughAtLeastD || i >= d) % MOD;
    }

    paths[weight][passedThroughAtLeastD] = maxPaths % MOD;
    return paths[weight][passedThroughAtLeastD];
}

int main() {
    int n, k, d;

    cin >> n >> k >> d;

    vector<vector<long long> > paths(n + 1, vector<long long>(2, -1));

    cout << countMaxPaths(paths, n, k, d, 0, false) << endl;

    return 0;
}