#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007

int main() {
    int n, k;
    long long keysSum = 0;

    cin >> n >> k;

    vector<long long> keysValue(n);
    vector<vector<long long> > comb(n + 1, vector<long long>(k + 1, 0));
    for (int i = 0; i < n; i++) {
        cin >> keysValue[i];
    }

    sort(keysValue.begin(), keysValue.end());
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j == 1 || i == j) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        keysSum += (comb[i][k] * keysValue[i - 1]);
        keysSum %= MOD;
    }

    cout << keysSum << endl;
    return 0;
}