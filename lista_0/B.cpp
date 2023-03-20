#include <iostream>
using namespace std;

int main() {
    int tests, n, alphabetSize;
    char letter;

    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> n;
        alphabetSize = 1;
        for (int j = 0; j < n; j++) {
            cin >> letter;
            alphabetSize = max(alphabetSize, letter - 'a' + 1);
        }
        cout << alphabetSize << endl;
    }
    
    return 0;
}