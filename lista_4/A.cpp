#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

int calculateMaxPieces(vector<int>& subresults, vector<int>& lengths, int currentSize) {
    if (currentSize == 0) {
        return 0;
    }

    if (subresults[currentSize] != -1) {
        return subresults[currentSize];
    }

    /*
    If the currentSize cannot be cut in at least one length, then we
    should return -INT_MIN as no left overs are allowed in the problem
    */
    int maxPieces = -INT_MIN;
    for (int i = 0; i < lengths.size(); i++) {
        if (currentSize - lengths[i] >= 0) {
            maxPieces = max(maxPieces, 1 + calculateMaxPieces(subresults, lengths, currentSize - lengths[i]));
        }
    }

    subresults[currentSize] = maxPieces;
    return maxPieces;
}

int main() {
    vector<int> inputs(3);
    int n;

    cin >> n >> inputs[0] >> inputs[1] >> inputs[2];

    vector<int> subresults(n + 1, -1);

    cout << calculateMaxPieces(subresults, inputs, n) << endl;

    return 0;
}