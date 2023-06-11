#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

class Graph {
    private:
        vector<vector<pair<int, int> > > nodes;
    public:
        Graph(int n) {
            nodes = vector<vector<pair<int, int> > >(n + 1);
        }

        void addEdge(int u, int v, int cost) {
            nodes[u].push_back(make_pair(v, cost));
        }

        vector<pair<int, int> > getConnectedNodes(int u) {
            return nodes[u];
        }
};

int findNumberOfMicesThatExitTheMaze(Graph& graph, int exit, int n, int timer) {
    int numberOfMicesThatExitTheMaze = 0, currentVertex, currentRemainingTime, adjacentVertex, cost;
    for (int i = 1; i <= n; i++) {
        queue<int> queue;
        vector<int> remainingTime(n, 0);

        remainingTime[i] = timer;
        queue.push(i);
        
        while (!queue.empty()) {
            currentVertex = queue.front();
            queue.pop();

            if (currentVertex == exit) {
                numberOfMicesThatExitTheMaze++;
                break;
            }

            currentRemainingTime = remainingTime[currentVertex];
            for (pair<int, int> edge : graph.getConnectedNodes(currentVertex)) {
                adjacentVertex = edge.first;
                cost = edge.second;

                if (currentRemainingTime - cost >= remainingTime[adjacentVertex]) {
                    remainingTime[adjacentVertex] = currentRemainingTime - cost;
                    queue.push(adjacentVertex);
                }
            }
        }
    }

    return numberOfMicesThatExitTheMaze;
}

int main() {
    int n, exit, t, m, u, v, cost;

    cin >> n;
    cin >> exit;
    cin >> t;
    cin >> m;

    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> cost;
        graph.addEdge(u, v, cost);
    }

    cout << findNumberOfMicesThatExitTheMaze(graph, exit, n, t) << endl;

    return 0;
}