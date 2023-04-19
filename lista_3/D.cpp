#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

void factorize(unordered_map<int, int>& factorsFreq, int x) {
    int sqrtOfX = sqrt(x);

    for (int i = 2; i <= sqrtOfX; i++) {
        while (x % i == 0) {
            factorsFreq.count(i) > 0 ? factorsFreq[i]++ : factorsFreq[i] = 1;
            x = x / i;
        }
    }

    if (x > 1) {
        factorsFreq.count(x) > 0 ? factorsFreq[x]++ : factorsFreq[x] = 1;
    }
}

/*
* Calculate the difference between the actual exponent of the factor in the number
* and the expected exponent. This will give the number of steps executed to change
* the actual into the expected.
*/
int calculateNumberOfSteps(int number, int factor, int factorFreq) {
    while (number > 0 && number % factor == 0) {
        factorFreq--;
        number /= factor;
    }

    return factorFreq > 0 ? factorFreq : 0;
}

/*
* The GCD is given by the product of all factors powered by the lowest exponent in the sequence.
* For example: 6, 10
* 6   = 2^1 + 3^1 + 5^0
* 10  = 2^1 + 3^0 + 5^1
* GCD = 2^1 * 3^0 * 5^0 = 2
* As the Max score can only be achieved when the lowest exponent is maximized, it's intuitive to think
* that the best scenario is to have the highest and lowest exponents almost equal (they can be off by at most one).
* The lowest exponent can be obtained by calculating the mean of the sum of all exponents.
*/
pair<long long, long long> computeResult(unordered_map<int, int>& factorsFreq, vector<int>& sequence) {
    long long score = 1, steps = 0;
    int n = sequence.size();

    // Calculate max score
    for (auto it = factorsFreq.begin(), end = factorsFreq.end(); it != end; ++it) {
        it->second /= n; // Calculate the mean = Get lowest exponent
        score *= pow(it->first, it->second);
    }

    // Calculate steps
    for (int i = 0; i < n; i++) {
        for (auto it = factorsFreq.begin(), end = factorsFreq.end(); it != end; ++it) {
            if (it->second > 0) {
                // If the mean is 0, we have no actions in order to maximize
                steps += calculateNumberOfSteps(sequence[i], it->first, it->second);
            }
        }
    }

    return make_pair(score, steps);
}

int main() {
    int n, current;
    vector<int> sequence;
    unordered_map<int, int> factorsFreq;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> current;
        sequence.push_back(current);
        factorize(factorsFreq, current);
    }

    pair<long long, long long> result = computeResult(factorsFreq, sequence);
    cout << result.first << " " << result.second << endl;
    return 0;
}