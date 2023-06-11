#include <iostream>
#include <vector>
#include <<algorithm>
using namespace std;

int main() {
    int n;
    long long result = 0;

    cin >> n;

    vector<long long> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());

    for (int i = 0; i < n; i++) {
        /*
        * Given a sorted list, the i'th position is added i times
        * and subtracted n - i - 1 times in the sum. Thus:
        * i * x - (n - i - 1) * x
        * (1 - n + i + 1) * x = (2 * i - n + 1) * x
        */
        result += ((2 * i - n + 1) * numbers[i]);
    }

    cout << result << endl;

    return 0;
}