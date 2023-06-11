#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007

#define N 1000000

int main() {
    int t, n;
    long long result;

    cin >> t;

    /*
        [i][0] = ith block is separate 
        [i][1] = ith block is just one
    */
    vector<vector<long long> > towers(N + 1, vector<long long>(2, 0));
    towers[1][0] = towers[1][1] = 1;
    for (int i = 2; i <= N; i++) {
        //                                      _  _
        // dp[i][1] = last blocks are separate | || |
        //                                   _ _
        // dp[i][2] = last blocks are fused |   |
        
        // transition:
        //              _  _    _  _    _  _    _  _     _ _
        //  _  _       | || |  |_|| |  | ||_|  |_||_|   |_ _|
        // | || | =>   | || |, | || |, | || |, | || |,  | | |
        //              _ _    _ _    _ _ 
        //  _ _        |   |  |_|_|  |_ _|
        // |   |  =>   |   |, |   |, |   |

        // dp[i][1] = dp[i-1][1]*4 + dp[i-1][2]
        // dp[i][2] = dp[i-1][1] + dp[i-1][2]*2
        towers[i][0] = (4 * towers[i - 1][0] % MOD + towers[i - 1][1]) % MOD;
        towers[i][1] = (towers[i - 1][0] + 2 * towers[i - 1][1] % MOD) %MOD;
    }

    for (int i = 0; i < t; i++) {
        cin >> n;

        result = (towers[n][0] + towers[n][1]) % MOD;
        cout << result << endl;
    }

    return 0;
}