#include <iostream>
#include <vector>
using namespace std;

bool checkIfTheArrayIsDivisibleInLessThanKComponentsWithLimitedSum(vector<int>& array, long long limitedSum, int k) {
    int components = 0, current;
    long long sum = 0;
    for (int i = 0, size = array.size(); i < size; i++) {
        current = array[i];
        sum += current;

        if (current > limitedSum)
            return false;

        if (sum > limitedSum) {
            components++;
            sum = current;
        }
    }
    components++;

    return components <= k;
}

int main() {
    int n, k;
    long long current, start = 0, end = 0, mid, solution;
    vector<int> array;

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> current;
        array.push_back(current);
        start = max(start, current);
        end += current;
    }

    while(start <= end) {
        mid = (start + end)/2;

        if(checkIfTheArrayIsDivisibleInLessThanKComponentsWithLimitedSum(array, mid, k)) {
            solution = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    cout << solution << endl;
    
    return 0;
}