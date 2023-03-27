#include <iostream>
using namespace std;

/*
k = bateria
a = just play
Pa = # de vezes em que 'a' aconteceu
b = play and charge
Pb = # de vezes em que 'b' aconteceu
n = steps

k - (Pa*a + Pb*b) > 0 e Pa + Pb = n
k > Pa*a + Pb*b

Pa + Pb = n
Pb = n - Pa

Juntando:
k > Pa*a + Pb*b
k > Pa*a + (n - Pa)*b
k > Pa*a + n*b - Pa*b
k > Pa*(a - b) + n*b
*/
bool checkIfVovaCanFinishTheGame(long long pa, long long a, long long b, long long n, long long k) {
    return k > pa*(a - b) + n*b;
}

int main() {
    int q;
    long long k, n, a, b, start, end, mid, solution;

    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> k >> n >> a >> b;

        start = 0;
        end = n;
        solution = -1;
        while (start <= end) {
            mid = (start + end)/2;
            if (checkIfVovaCanFinishTheGame(mid, a, b, n, k)) {
                solution = mid;
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        cout << solution << endl;
    }
    
    return 0;
}
