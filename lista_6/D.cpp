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

        pair<int, int> dfs(vector<bool>& visited, int depth, int vertex) {
            visited[vertex] = true;

            pair <int, int> currentMaxDepth;
            pair <int, int> maxDepth(vertex, depth);
            depth++;
            for (int neighbor : getConnectedNodes(vertex)) {
                if (!visited[neighbor]) {
                    currentMaxDepth = dfs(visited, depth, neighbor);
                    if (currentMaxDepth.second > maxDepth.second) {
                        maxDepth = pair<int, int>(currentMaxDepth);
                    }
                }
            }

            return maxDepth;
        }
};

int getMaxTreeDiameter(Graph graph, int n) {
    vector<bool> visited(n + 1, false);
    vector<int> depth(n + 1, 0);
    pair<int, int> maxDepth;

    maxDepth = graph.dfs(visited, 0, 1);

    visited.clear();
    visited.resize(n + 1, false);
    
    maxDepth = graph.dfs(visited, 0, maxDepth.first);

    return maxDepth.second;
}

int main() {
    int n, u, v;

    cin >> n;

    Graph graph(n);


    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    cout << getMaxTreeDiameter(graph, n) << endl;
    return 0;
}
