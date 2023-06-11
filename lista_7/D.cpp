#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
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
            nodes[v].push_back(make_pair(u, cost));
        }

        vector<pair<int, int> > getConnectedNodes(int u) {
            return nodes[u];
        }
};

vector<int> dijkstra(Graph& graph, int n) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > minHeap;
    vector<int> distance(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    vector<int> visited(n + 1, false);
    int currentVertex, adjacentVertex, cost;

    distance[1] = 0;
    // The distance must be the first for the minHeap to work
    minHeap.push(make_pair(distance[1], 1));
    
    while (!minHeap.empty()){
        currentVertex = minHeap.top().second;
        minHeap.pop();

        if (currentVertex == n) break;

        visited[currentVertex] = true;

        for (pair<int, int> edge : graph.getConnectedNodes(currentVertex)) {
            adjacentVertex = edge.first;
            cost = edge.second;

            if (!visited[adjacentVertex] && distance[adjacentVertex] > distance[currentVertex] + cost) {
                parent[adjacentVertex] = currentVertex;
                distance[adjacentVertex] = distance[currentVertex] + cost;
                minHeap.push(make_pair(distance[adjacentVertex],adjacentVertex));
            }
        }
    }

    vector<int> reversedPath;
    if (distance[n] == INT_MAX) {
        reversedPath.push_back(-1);
    } else {
        while(currentVertex != -1) {
            reversedPath.push_back(currentVertex);
            currentVertex = parent[currentVertex];
        }
    }

    return reversedPath;
}

int main() {
    int n, m, u, v, cost;

    cin >> n >> m;

    Graph graph(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> cost;
        graph.addEdge(u, v, cost);
    }

    vector<int> reversedPath = dijkstra(graph, n);

    for (int i = reversedPath.size() - 1; i >= 0; i--) {
        cout << reversedPath[i] << " ";
    }

    cout << endl;

    return 0;
}