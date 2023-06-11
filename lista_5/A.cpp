#include <iostream>
#include <vector>
using namespace std;

template <const int MOD>
struct mint {
    long long x;
    mint(): x(0) {}
    mint(long long _x): x(_x%MOD<0?_x%MOD+MOD:_x%MOD) {}
    void operator+=(mint rhs) { x+=rhs.x; if(x>=MOD) x-=MOD; }
    void operator-=(mint rhs) { x-=rhs.x; if(x<0)x+=MOD; }
    void operator*=(mint rhs) { x*=rhs.x; x%=MOD; }
    void operator/=(mint rhs) { *this *= rhs.inv(); }
    mint operator+(mint rhs) { mint res=*this; res+=rhs; return res; }
    mint operator-(mint rhs) { mint res=*this; res-=rhs; return res; }
    mint operator*(mint rhs) { mint res=*this; res*=rhs; return res; }
    mint operator/(mint rhs) { mint res=*this; res/=rhs; return res; }
    mint inv() { return this->pow(MOD-2); }
    mint pow(long long e) {
        mint res(1);
        for(mint p=*this;e>0;e/=2,p*=p) if(e%2)
            res*=p;
        return res;
    }
};

using Z = mint<1000000007>;

Z calculateBinomialCoefficients(vector<Z>& factorials, int a, int b) {
    for (int i = factorials.size(); i <= a; i++) {
        factorials.push_back(factorials[i - 1] * i);
    }

    return factorials[a] / (factorials[b] * factorials[a - b]);
}

int main() {
    int n, a, b;
    vector<Z> factorials;
    factorials.push_back(1);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        cout << calculateBinomialCoefficients(factorials, a, b).x << endl;
    }

	return 0;
}
