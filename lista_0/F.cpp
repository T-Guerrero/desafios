#include <iostream>
using namespace std;

int main() {
    int tests, n, l, antPosition, earliestTime, latestTime;

    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> l >> n;

        earliestTime = 0;
        latestTime = 0;
        for (int j = 0; j < n; j++) {
            cin >> antPosition;

            earliestTime = max(earliestTime, min(antPosition, l - antPosition));
            latestTime = max(latestTime, max(antPosition, l - antPosition));
        }

        cout << earliestTime << " " << latestTime << endl;
    }

    return 0;
}