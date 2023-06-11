#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAX_N 200000
#define MAX_LOG_N 17

int binaryLifting[MAX_N + 1][MAX_LOG_N + 1];

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

void calculateBinaryLifting(int currentNode, int parentNode) {
    binaryLifting[currentNode][0] = parentNode;
    for (int i = 1; i <= MAX_LOG_N; i++) {
        binaryLifting[currentNode][i] = binaryLifting[ binaryLifting[currentNode][i - 1] ][i - 1];
    }
}

void populateNodesDepthAndBinaryLifting(vector<int>& depth, Graph& graph, int currentNode, int parentNode) {
    calculateBinaryLifting(currentNode, parentNode);
    for (int child : graph.getConnectedNodes(currentNode)) {
        depth[child] = depth[currentNode] + 1;
        populateNodesDepthAndBinaryLifting(depth, graph, child, currentNode);
    }
}

// Function to return the LCA of nodes u and v using Binary Lifting
int lca(vector<int>& depth, int u, int v) {
    int farthestNode, closestNode;
    farthestNode = depth[u] > depth[v] ? u : v;
    closestNode = depth[u] > depth[v] ? v : u;

    // Find the ancestor of the farthestNode which is at the same level as the closestNode
    for (int i = MAX_LOG_N; i >= 0; i--) {
        int pot = 1 << i; // 2 ^ i
        if (depth[farthestNode] - pot >= depth[closestNode]) {
            farthestNode = binaryLifting[farthestNode][i];
        }
    }
 
    if (farthestNode == closestNode) {
        return farthestNode;
    }
 
    for (int i = MAX_LOG_N; i >= 0; i--) {
        if (binaryLifting[farthestNode][i] != binaryLifting[closestNode][i]) {
            farthestNode = binaryLifting[farthestNode][i];
            closestNode = binaryLifting[closestNode][i];
        }
    }
 
    return binaryLifting[farthestNode][0];
}

int main() {
    // fast read
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q, boss, u, v;

	cin >> n >> q;

    vector<int> depth(n + 1, 0);
    Graph graph(n);
    for (int i = 2; i <= n; i++) {
        cin >> boss;
        graph.addEdge(boss, i);
    }

    populateNodesDepthAndBinaryLifting(depth, graph, 1, 1);

    for (int i = 0; i < q; i++) {
        cin >> u >> v;
		cout << lca(depth, u, v) << endl;
    }

    return 0;
}