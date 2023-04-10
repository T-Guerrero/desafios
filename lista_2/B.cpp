#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n, current, solution = 0;
    unordered_map<int, int> socksPerColor;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> current;
        socksPerColor.count(current) > 0 ? socksPerColor[current]++ : socksPerColor[current] = 1;
    }

    for (auto it = socksPerColor.begin(), end = socksPerColor.end(); it != end; ++it) {
        solution += it->second / 2;
    }

    cout << solution << endl;

    return 0;
}