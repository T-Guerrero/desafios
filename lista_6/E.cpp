#include <iostream>
#include <vector>
using namespace std;

class Graph {
    private:
        vector<vector<int> > nodes;
    public:
        Graph(int n) {
            nodes = vector<vector<int> >(n + 1);
        }

        void addEdge(int u, int v) {
            nodes[u].push_back(v);
            nodes[v].push_back(u);
        }

        vector<int> getConnectedNodes(int u) {
            return nodes[u];
        }

        bool searchForComponentsWithCycles(vector<bool>& visited, int vertex) {
            visited[vertex] = true;

            bool hasACycle = true;
            for (int neighbor : getConnectedNodes(vertex)) {
                if (!visited[neighbor]) {
                    hasACycle = searchForComponentsWithCycles(visited, neighbor);
                }
            }

            if (nodes.size() < 3 || getConnectedNodes(vertex).size() != 2) {
                hasACycle = false;
            }

            return hasACycle;
        }
};

int main() {
    int n, m, u, v, numberOfConnectedComponents = 0;

    cin >> n >> m;

    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (graph.searchForComponentsWithCycles(visited, i) == true) {
                numberOfConnectedComponents ++;
            }
        }
    }

    cout << numberOfConnectedComponents << endl;

    return 0;
}