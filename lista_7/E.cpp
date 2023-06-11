#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define MAX 100000

class Graph {
    private:
        vector<vector<int> > nodes;
    public:
        Graph(int n) {
            nodes = vector<vector<int> >(n + 1);
        }

        void addEdge(int u, int v) {
            nodes[u].push_back(v);
        }

        vector<int> getConnectedNodes(int u) {
            return nodes[u];
        }
};

int findMinNumberOfJumps(Graph & graph, int n) {
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > minHeap;
    vector<int> distance(MAX + 10, 0);
    pair<int, int> current;
    int currentDistance, currentIndex;
    
    distance[0] = 1;
    minHeap.push(make_pair(distance[0], 0));
    
    while (!minHeap.empty()) {
        current = minHeap.top();
        currentDistance = current.first;
        currentIndex = current.second;

        minHeap.pop();
        
        for (int adjacent : graph.getConnectedNodes(currentIndex)) {
            if (distance[adjacent] == 0 || distance[currentIndex] + 1 < distance[adjacent]) {
                if (adjacent >= MAX) {
                    distance[adjacent] = distance[currentIndex];
                } else {
                    distance[adjacent] = distance[currentIndex] + 1;
                }
                minHeap.push(make_pair(distance[adjacent], adjacent));
            }
        }
    }

    return distance[n - 1] - 1;
}

int main() {
    Graph graph(MAX + 10); // ten more for each digit (0 to 9)
    string digits;
    int n;

    cin >> digits;

    n = digits.length();
    for (int i = 0; i < n; i++) {
        graph.addEdge(i, digits[i] - '0' + MAX);
        graph.addEdge(digits[i] - '0' + MAX, i);

        if (i > 0) {
            graph.addEdge(i, i - 1);
        }
        if (i < n - 1) {
            graph.addEdge(i, i + 1);
        }
    }

    cout << findMinNumberOfJumps(graph, n) << endl;

    return 0;
}