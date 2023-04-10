#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    string input;
    map<vector<long long>, int> patterns;
    vector<long long> freq(10, 0);
    long long numberOfOcurrences = 0, result = 0, current;

    cin >> input;

    patterns[freq] = 1;
    for (int i = 0; i < input.size(); i++) {
        current = freq[input[i] - '0'];
        freq[input[i] - '0'] = (current + 1) % 2;

        patterns.count(freq) > 0 ? patterns[freq]++ : patterns[freq] = 1;
    }

    for (auto it = patterns.begin(), end = patterns.end(); it != end; ++it) {
        numberOfOcurrences = it->second;
        result += (numberOfOcurrences * (numberOfOcurrences - 1)) / 2; // Cn,2 = n!/(n-2)!*2!
    }

    cout << result << endl;
    return 0;
}