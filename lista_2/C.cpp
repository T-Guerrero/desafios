#include <iostream>
#include <vector>
// Use the flag -std=c++11 to compile
#include <tuple>
using namespace std;

int main() {
    int n, m, k, current, l, r, d, x, y;
    vector<tuple<int, int, int> > operations;
    tuple<int, int, int> operation;
    vector<int> array;
    long long totalTimes = 0, totalSum = 0;


    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        cin >> current;
        array.push_back(current);
    }

    for (int i = 0; i < m; i++) {
        // Read operations
        cin >> l >> r >> d;
        operations.push_back(make_tuple(l - 1, r - 1, d));
    }

    vector<long long> times(m + 1, 0);
    for (int i = 0; i < k; i++) {
        // Read queries and count how many times the operations happen
        cin >> x >> y;
        x--;
        y--;
        times[x]++;
        times[y + 1]--;
    }

    vector<long long> sum(n + 1, 0);
    for (int i = 0; i < m; i++) {
        operation = operations[i];
        totalTimes += times[i];
        sum[get<0>(operation)] += totalTimes * get<2>(operation);
        sum[get<1>(operation) + 1] -= totalTimes * get<2>(operation);
    }

    for (int i = 0; i < n; i++) {
        totalSum += sum[i];
        cout << array[i] + totalSum << ' ';
    }

    cout << endl;

    return 0;
}