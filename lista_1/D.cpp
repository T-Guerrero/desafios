#include <iostream>
#include <vector>
#include <limits>
#include <utility>
using namespace std;

bool checkIfTheSmallestFlowerCanGrowToH(vector<long long>& flowersHeight, long long h, int numberOfDays, int range) {
    vector<int> decreaseWatering(flowersHeight.size(), 0);
    int daysUsed = 0, accumulatedWatering = 0;
    long long diff;
    for (int i = 0, size = flowersHeight.size(); i < size; i++) {
        accumulatedWatering -= decreaseWatering[i];
        if (flowersHeight[i] < h) {
            diff = h - flowersHeight[i] - accumulatedWatering;

            if (diff <= 0) {
                continue;
            } else if (numberOfDays - daysUsed >= diff) {
                // Can start watering
                accumulatedWatering += diff;
                if (i + range < size) {
                    decreaseWatering[i + range] = diff;
                }
                daysUsed += diff;
            } else {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n, m, w;
    long long currentFlowerHeight, start = INT_MAX, end = 0, mid, solution;
    vector<long long> flowersHeight;

    cin >> n >> m >> w;

    for (int i = 0; i < n; i++) {
        cin >> currentFlowerHeight;
        flowersHeight.push_back(currentFlowerHeight);
        start = min(start, currentFlowerHeight);
        end = max(end, currentFlowerHeight + m);
    }

    while(start <= end) {
        mid = (start + end)/2;

        if(checkIfTheSmallestFlowerCanGrowToH(flowersHeight, mid, m, w)) {
            solution = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    cout << solution << endl;
    
    return 0;
}