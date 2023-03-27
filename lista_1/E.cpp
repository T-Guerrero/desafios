#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 
using namespace std;

int main() {
    int n, current;
    double l;
    vector<int> lanterns;

    cin >> n >> l;

    for (int i = 0; i < n; i++) {
        cin >> current;
        lanterns.push_back(current);
    }

    sort(lanterns.begin(), lanterns.end());

    // Left over or right over
    double d = max((double) lanterns[0], l - lanterns[lanterns.size() - 1]);

    for(int i = 0; i < lanterns.size() - 1; i++) {
        d = max(d, ((double) lanterns[i + 1] - lanterns[i])/2);
    }
    
    cout << setprecision(9) << d;
    return 0;
}