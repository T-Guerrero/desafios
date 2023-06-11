#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007

unsigned long long calculateNumberOfTriples(vector<unsigned long long>& n) {
    sort(n.begin(), n.end());
    
    n[0] %= MOD;
    n[1] %= MOD;
    n[2] %= MOD;
    
    return (
        (((n[0] % MOD) *
        (n[1] - 1 + MOD)) % MOD *
        (n[2] - 2 + MOD)) % MOD
    );
}

int main() {
    int t;
    vector<unsigned long long> n(3);

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n[0] >> n[1] >> n[2];
    
        cout << calculateNumberOfTriples(n) << endl;
    }

    return 0;
}