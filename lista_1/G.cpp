#include <iostream>
#include <vector>
using namespace std;

void sendQuery(int k, int start, int end) {
    string query = string("?") + ' ' + to_string(k);
    for (int i = start; i <= end; i++) {
        query += " " + to_string(i);
    }
    
    cout << query << endl;
    cout.flush();
}

void sendResult(int result) {
    cout << string("!") + ' ' + to_string(result) << endl;
    cout.flush();
}

bool PilesSumDiffer(vector<int>& piles, int start, int end) {
    int pilesSum = 0, actualSum;
    for (int i = start; i <= end; i++) {
        pilesSum += piles[i];
    }
    
    sendQuery(end-start+1, start+1, end+1);
    cin >> actualSum;

    return pilesSum != actualSum;
}

int main() {
    int tests, n, current;

    cin >> tests;

    for (int i = 0; i < tests; i++) {
        cin >> n;

        vector<int> piles;
        for (int j = 0; j < n; j++) {
            cin >> current;
            piles.push_back(current);
        }

        int start = 0, end = piles.size() - 1, mid;
        while(start <= end) {
            mid = (start + end + 1)/2;
            if (PilesSumDiffer(piles, start, mid)) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        sendResult(start + 1);
    }
    
    return 0;
}