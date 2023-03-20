#include <iostream>
using namespace std;

int main() {
    int tests, a, b;

    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> a >> b;

        cout << a + b << endl;
    }
    
    return 0;
}