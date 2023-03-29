#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int lastAirFlowSeen = 0;
    long long n, h, result = 0, maxDistanceUsingFlows = 0, heightNeeded = 0;
    vector<pair<long long, long long> > ascendingAirFlows;
    pair<long long, long long> current;

    cin >> n >> h;
    for (int i = 0; i < n; i++) {
        cin >> current.first >> current.second;
        ascendingAirFlows.push_back(pair<long long, long long>(current));
    }


    for (int i = 0; i < n; i++) {
        if (i > 0) {
            // Distance between asceding air flows
            heightNeeded += ascendingAirFlows[i].first - ascendingAirFlows[i - 1].second;
            while (heightNeeded >= h) {
                // Remove the last seen asceding air flow
                heightNeeded -= ascendingAirFlows[lastAirFlowSeen + 1].first - ascendingAirFlows[lastAirFlowSeen].second;
                maxDistanceUsingFlows -= ascendingAirFlows[lastAirFlowSeen].second - ascendingAirFlows[lastAirFlowSeen].first;

                lastAirFlowSeen++;
            }
        }

        maxDistanceUsingFlows += ascendingAirFlows[i].second - ascendingAirFlows[i].first;
        result = max(maxDistanceUsingFlows, result);
    }

    result += h;

    cout << result << endl;
    return 0;
}