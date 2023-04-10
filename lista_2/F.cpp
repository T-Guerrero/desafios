#include <iostream>
using namespace std;

int main() {
    int t, n, solution, neededTime, currentPossibleStartPoint;
    char symbol;
    string pattern;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n >> symbol;
        cin >> pattern;
        solution = 0;
        currentPossibleStartPoint = -1;
        neededTime = 0;

        pattern += pattern;

        for (int j = 0; j < pattern.length(); j++) {
            if (pattern[j] == 'g') {
                solution = max(solution, neededTime);
                currentPossibleStartPoint = -1;
                neededTime = 0;
            } else if (currentPossibleStartPoint != -1) {
                neededTime++;
            } else if (pattern[j] == symbol) {
                currentPossibleStartPoint = j;
                neededTime++;
            }
        }

        cout << solution << endl;
    }

    return 0;
}