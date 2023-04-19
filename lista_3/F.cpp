#include <iostream>
#include <math.h>
using namespace std;

/*
* The number of occurrences of a factor in a factorial series (x!) is given by
* the sum of the divisions of x by each power of the factor until it becomes zero.
* For example: x = 1000 and factor = 5
* 5^4 = 625, but 5^5 = 3125 > 1000, so:
* occurrences = 1000/5 + 1000/5^2 + 1000/5^3 + 1000/5^4
* occurrences = 200 + 40 + 8 + 1.6 = 249.6 = 249
*/
int occurrencesOfFactorInXFactorial(int x, int factor) {
    int occurrences = 0;
    while(x > 0) {
        x = x/factor;
        occurrences += x;
    }

    return occurrences;
}

int main() {
    int t, n, numberOfZeros;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        // The number of 0's is equal to the number of 2*5=10's
        numberOfZeros = min(occurrencesOfFactorInXFactorial(n, 2), occurrencesOfFactorInXFactorial(n, 5));
        cout << numberOfZeros << endl;
    }
}