#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 5;
int n, h, x1[N], x2[N];

bool valid(int x) {
    int t = 0;
    for (int i = 1; i <= n; i++) {
        if (x < x1[i]) continue; // fora do segmento, não precisa se preocupar
        int dist = min(x2[i], x) - x1[i]; // comprimento do trecho dentro do segmento
        int alt = h - dist; // altitude do planador ao chegar no fim do trecho dentro do segmento
        if (alt <= 0) return false; // planador não consegue subir
        t += dist + alt - h; // tempo gasto no trecho
        x = x2[i]; // planador chega no fim do trecho e avança para o próximo segmento
    }
    return t <= x; // verifica se o tempo total gasto é menor ou igual ao tempo que o planador tem
}

signed main() {
    cin >> n >> h;
    for (int i = 1; i <= n; i++) {
        cin >> x1[i] >> x2[i];
    }

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (valid(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;

    return 0;
}
