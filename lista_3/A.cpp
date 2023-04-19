#include <iostream>
using namespace std;

#define TARGET_NUMBER 1378

long long recursiveExponentiation(int expoent, int mod) {
    if (expoent == 0)
        return 1;

    long long subResult = recursiveExponentiation(expoent/2, mod);

    if (expoent % 2 == 0) {
        // x^n = (x^{n/2})^2
        return subResult * subResult % mod;
    } else {
        // x^n = (x^{n-1/2})^2 * x
        return (subResult * subResult) * TARGET_NUMBER % mod;
    }
}

int main() {
    int n;

    cin >> n;

    cout << recursiveExponentiation(n, 10) << endl;
    return 0;
}