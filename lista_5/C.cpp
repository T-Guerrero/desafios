#include <iostream>
using namespace std;

#define MOD 998244353

long long calculateNumberOfBeautifulPermutations(int n) {
    if (n % 2 != 0) {
        return 0;
    }

    long long permutations = 1;
    for (int i = 2; i <= n/2; i++) {
        permutations = (permutations * i) % MOD;
    }

    return (permutations * permutations) % MOD;
}

int main() {
    int t, n;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        cout << calculateNumberOfBeautifulPermutations(n) << endl;
    }

    return 0;
}