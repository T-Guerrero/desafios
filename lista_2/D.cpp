#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t, n, current, currentIndex, currentFactorial;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<int> sequence, results(n);
        for (int j = 0; j < n; j++) {
            cin >> current;
            sequence.push_back(current);
        }

        currentIndex = n - 1;
        currentFactorial = 0;

        while(currentIndex >= 0 && sequence[currentIndex] >= currentFactorial + 1) {
            // currentIndex can be part of the solution
            currentFactorial++;
            currentIndex--;
        }

        for(int j = n - 1; j >= 0; j--) {
            results[j] = currentFactorial;

            if (currentIndex >= 0 && sequence[currentIndex] >= currentFactorial) {
                // currentIndex can be part of the solution
                currentIndex--;
            } else {
                // currentIndex can't be part of the solution 
                currentFactorial--;
            }
        }

        for (int j = 0; j < n; j++) {
            cout << results[j] << " ";
        }

        cout << endl;
    }

    return 0;
}