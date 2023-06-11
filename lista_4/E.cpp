#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string computeLcs(vector<vector<int> >& lcsTable, string x1, string x2) {
    for (int i = 0; i < x1.length(); i++) {
        for (int j = 0; j < x2.length(); j++) {
            lcsTable[i + 1][j + 1] = (x1[i] == x2[j]) ? 
                                    lcsTable[i][j] + 1 : max(lcsTable[i][j + 1], lcsTable[i + 1][j]);
        }
    }

    string lcs = "";
    int x1Index = x1.length() - 1, x2Index = x2.length() - 1;
    while (x1Index >= 0 && x2Index >= 0) {
        if (x1[x1Index] == x2[x2Index]) {
            lcs += x1[x1Index];
            x1Index--; x2Index--;
        } else if (lcsTable[x1Index][x2Index + 1] >= lcsTable[x1Index + 1][x2Index]) {
            x1Index--;
        } else {
            x2Index--;
        }
    }
    
    reverse(lcs.begin(), lcs.end());

    return lcs;
}

int main() {
    string x, t, result;

    cin >> x;
    cin >> t;

    vector<vector<int> > lcsTable(x.length() + 1, vector<int>(t.length() + 1, 0));
    result = computeLcs(lcsTable, x, t);

    cout << result << endl;
    return 0;
}