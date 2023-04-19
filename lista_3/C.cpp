#include <iostream>
#include <vector>
using namespace std;

#define CRIVO_SIZE 10e3 + 1

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

int main() {
    int k, n;
    vector<bool> isNotPrime(CRIVO_SIZE, false);
    vector<int> queries;

    eratosthenesSieve(isNotPrime);

    cin >> n;

    for (int i = 2; i <= n; i++) {
        if(!isNotPrime[i]) {
            for (int multiple = 1; multiple <= n/i; multiple *= i) {
                queries.push_back(multiple * i);
            }
        }
    }

    cout << queries.size() << endl;

    for (int i = 0; i < queries.size(); i++) {
        cout << queries[i] << ' ';
    }
    cout << endl;

    return 0;
}