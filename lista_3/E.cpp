#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

#define CRIVO_SIZE 10e6

// This solution don't pass due to TLE, however it produces a correct result
bool numberOfDivisorsOfXAreEqualTo(long long x, int expected) {
    long long sqrtOfX = sqrt(x);
    int divisors = 2;

    for (int i = 2; i <= sqrtOfX && divisors <= expected; i++) {
        if (x % i == 0) {
            divisors++;
            if (x/i > sqrtOfX) {
                // If i|x, then x/i|x
                divisors++;
            }
        }
    }

    return divisors == expected;
}

void eratosthenesSieve(vector<bool>& isNotPrime) {
    if (isNotPrime.size() < 2) {
        // Does not make sense to calculate the Sieve 
        return;
    }

    isNotPrime[0] = isNotPrime[1] = true;
    for (int i = 2; i < isNotPrime.size(); i++) {
        if (!isNotPrime[i]) {
            for (int j = 2*i; j < isNotPrime.size(); j+=i) {
                // Mark multiples as not prime
                isNotPrime[j] = true;
            }
        }
    }
}

/*
* Given a prime number p, then p^2 will have exaclty 3 divisors (1, p, p^2).
* This method uses the inverse logic, get a sqrt of a number and:
* - Check if it is a prime number
* - Check if it is a perfect squre
*/
bool numberOfDivisorsOfXIsEqualsTo3(vector<bool>& isNotPrime, long long x) {
    long long sqrtOfX = sqrt(x);
    return !isNotPrime[sqrtOfX] && sqrtOfX*sqrtOfX == x;
}

int main() {
    int n;
    long long current;
    vector<bool> isNotPrime(CRIVO_SIZE, false);

    eratosthenesSieve(isNotPrime);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> current;
        cout << (numberOfDivisorsOfXIsEqualsTo3(isNotPrime, current) ? "YES" : "NO") << endl;
    }

    return 0;
}