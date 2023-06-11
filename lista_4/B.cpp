#include <iostream>
#include <vector>
using namespace std;

// This is an alternative solution to the Knapsack Problem because W can be too big
int findMaxKnapsackValue(int maxWeight, int n, vector<int>& weights, vector<int>& values) {
    int maxPossibleValue = 0, actualMaxValue = 0, currentWeight, currentValue;

    for (int i = 0; i < n; i++) {
        maxPossibleValue += values[i];
    }

    vector<long long> knapsackWeightPerValue(maxPossibleValue + 1, INT_MAX);

    knapsackWeightPerValue[0] = 0;

    for (int i = 0; i < n; i++) {
        currentWeight = weights[i];
        currentValue = values[i];

        for (int v = maxPossibleValue - currentValue; v >= 0; v--) {
            knapsackWeightPerValue[v + currentValue] = min(knapsackWeightPerValue[v + currentValue], knapsackWeightPerValue[v] + currentWeight);
        }
    }

    for (int v = maxPossibleValue; v >= 0 && actualMaxValue == 0; v--) {
        if (knapsackWeightPerValue[v] <= maxWeight) {
            actualMaxValue = v;
        }
    }

    return actualMaxValue;
}

int main() {
    int n, w;

    cin >> n >> w;

    vector<int> weights(n), values(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i] >> values[i];
    }

    cout << findMaxKnapsackValue(w, n, weights, values) << endl;

    return 0;
}