#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAX_N 200000
#define MAX_LOG_N 17

int binaryLifting[MAX_N + 1][MAX_LOG_N + 1];

/*
binaryLifting[i][b]: the 2^b boss of i
*/
void calculateBinaryLifting(vector<int>& boss, int n) {
    for(int i = 2; i <= n; i++) {
        binaryLifting[i][0] = boss[i];
    }

    for (int j = 1; j <= MAX_LOG_N; j++) {
        for (int i = 1; i <= n; i++) {
            binaryLifting[i][j] = binaryLifting[ binaryLifting[i][j - 1] ][j - 1];
        }
    }
}

int calculateKthBoss(int employee, int k) {
    int boss = employee;
    for (int i = 0; i <= MAX_LOG_N && k > 0; i++) {
        if (k % 2 == 1) {
            boss = binaryLifting[boss][i];
        }
        k /= 2;
    }

    return boss < 1 ? -1 : boss;
}

int main() {
    // fast read
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q, x, k;

	cin >> n >> q;

    vector<int> boss(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> boss[i];
    }

    calculateBinaryLifting(boss, n);

    for (int i = 0; i < q; i++) {
        cin >> x >> k;
		cout << calculateKthBoss(x, k) << endl;
    }

    return 0;
}