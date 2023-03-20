#include <iostream>
using namespace std;

#define EVEN_TYPE 0
#define ODD_TYPE 1   

int main() {
    int tests, n, q, type, x, evenNumbers, oddNumbers;
    long long sum, currentNumber;

    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> n >> q;

        evenNumbers = oddNumbers = 0;
        sum = 0;
        for (int j = 0; j < n; j++) {
            cin >> currentNumber;

            sum += currentNumber;

            if ((currentNumber % 2) == 0) {
                evenNumbers++;
            } else {
                oddNumbers++;
            }
        }

        for (int j = 0; j < q; j++) {
            cin >> type >> x;

            sum += x * ((type == EVEN_TYPE) ? evenNumbers : oddNumbers);

            switch (type) {
            case EVEN_TYPE:
                if ((x % 2) != 0) {
                    // Even + Odd = Odd
                    oddNumbers += evenNumbers;
                    evenNumbers = 0;
                }
                break;            
            case ODD_TYPE:
                if ((x % 2) != 0) {
                    // Odd + Odd = Even
                    evenNumbers += oddNumbers;
                    oddNumbers = 0;
                }
                break;
            default:
                break;
            }

            cout << sum << endl;
        }
    }

    return 0;
}