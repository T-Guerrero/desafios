#include <iostream>
#include <vector>
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
            nodes[v].push_back(u);
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
        if (child != parentNode) {
            depth[child] = depth[currentNode] + 1;
            populateNodesDepthAndBinaryLifting(depth, graph, child, currentNode);
        }
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

long long calculateDistanceBetweenNodes(vector<int>& depth, int node1, int node2) {
    int lcaNode = lca(depth, node1, node2);
    return depth[node1] + depth[node2] - 2 * depth[lcaNode];
}

int main() {
    int n, q, u, v;

    cin >> n >> q;

    vector<int> depth(n + 1, 0);
    Graph graph(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    populateNodesDepthAndBinaryLifting(depth, graph, 1, 0);

    for (int i = 0; i < q; i++) {
        cin >> u >> v;
        cout << calculateDistanceBetweenNodes(depth, u, v) << endl;
    }
    
    return 0;
}