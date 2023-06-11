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

        int dfs(vector<bool>& visited, int vertex) {
            visited[vertex] = true;

            int count = 1;
            for (int neighbor : getConnectedNodes(vertex)) {
                if (!visited[neighbor]) {
                    count += dfs(visited, neighbor);
                }
            }

            return count;
        }
};

bool isCthulhu(Graph graph, int n, int m) {
    vector<bool> visited(n + 1, false);
    int count = graph.dfs(visited, 1);

    return n == count && n == m;
}

int main() {
    int n, m, u, v;

    cin >> n >> m;

    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    cout << (isCthulhu(graph, n, m) ? "FHTAGN!" : "NO") << endl;

    return 0;
}