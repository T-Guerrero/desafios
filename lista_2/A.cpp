#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int n, q, current;
    pair<int, int> query;
    long long sum = 0;
    vector<long long> cumulativeSum;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> current;
        sum += current;
        cumulativeSum.push_back(sum);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> query.first >> query.second;
        cout << cumulativeSum[query.second] - (query.first > 0 ? cumulativeSum[query.first - 1] : 0) << endl;
    }

    return 0;
}