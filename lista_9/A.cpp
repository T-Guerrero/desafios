#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAX_N 200000
#define MAX_LOG_K 29

// Declared as C array because of the time limit
int binaryLifting[MAX_N + 1][MAX_LOG_K + 1];

/* 
binaryLifting[i][b]: onde eu chego após usar o teleportador 2^b vezes em i
                     note que binaryLifting[i][0] = teleporter[i], pois 2^0 == 1
                     para calcular, utilizamos que binaryLifting[i][b] = binaryLifting[binaryLifting[i][b-1]][b-1]
*/
void calculateBinaryLifting(vector<int>& teleporter, int n) {
    for(int i = 1; i <= n; i++) {
        binaryLifting[i][0] = teleporter[i];
    }

    for (int j = 1; j <= MAX_LOG_K; j++) {
        for (int i = 1; i <= n; i++) {
            binaryLifting[i][j] = binaryLifting[ binaryLifting[i][j - 1] ][j - 1];
        }
    }
}

// calcula onde eu chego após começar no planeta i e utilizar o teleportador k vezes
int calculateDestination(int planet, int travelLength) {
    for (int i = floor(log2(travelLength)); travelLength > 0; i = floor(log2(travelLength))) {
        int pot = 1 << i; // 2 ^ i
        travelLength -= pot;
        planet = binaryLifting[planet][i];
    }

    return planet;
}

int main() {
    // fast read
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q, startPlanet, travelLength;
    cin >> n >> q;
    vector<int> teleporter(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> teleporter[i];
    }

    calculateBinaryLifting(teleporter, n);

    for (int i = 0; i < q; i++) {
        cin >> startPlanet >> travelLength;
        cout << calculateDestination(startPlanet, travelLength) << endl;
    }

    return 0;
}