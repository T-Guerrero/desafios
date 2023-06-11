#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

#define MAX_N 200000
#define MAX_LOG_N 17

int binaryLifting[MAX_N + 1][MAX_LOG_N + 1];

// Heavy Light Decomposition
int hld[MAX_N + 1][MAX_LOG_N + 1];

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

class UnionFind {
    private:
        vector<int> parent;
        vector<int> componentSize;
    public:
        UnionFind(int n) {
            for (int i = 0; i <= n; i++) {
                parent.push_back(i);
                componentSize.push_back(1);
            }
        }

        int find(int vertex) {
            if (parent[vertex] == vertex) {
                return vertex;
            }

            int rep = find(parent[vertex]);

            // Optimization
            parent[vertex] = rep;

            return rep;
        }

        bool join(int vertex1, int vertex2) {
            int rep1 = find(vertex1);
            int rep2 = find(vertex2);

            if (rep1 == rep2) return false;

            // Optimization
            if (componentSize[rep1] > componentSize[rep2]) {
                parent[rep2] = rep1;
                componentSize[rep1] += componentSize[rep2];
            } else {
                parent[rep1] = rep2;
                componentSize[rep2] += componentSize[rep1];
            }
			return true;
        }
};

void calculateHeavyLightDecomposition(int currentNode, int w) {
	hld[currentNode][0] = w;
	for (int i = 1; i < MAX_LOG_N + 1; i++) {
		hld[currentNode][i] = max(hld[currentNode][i - 1], hld[ binaryLifting[currentNode][i - 1] ][i - 1]);
	}
}

void calculateBinaryLifting(int currentNode, int parentNode) {
    binaryLifting[currentNode][0] = parentNode;
    for (int i = 1; i <= MAX_LOG_N; i++) {
        binaryLifting[currentNode][i] = binaryLifting[ binaryLifting[currentNode][i - 1] ][i - 1];
    }
}

void dfs(vector<int>& depth, Graph& graph, int currentNode, int parentNode, int w) {
	int adjNode, cost;
    
	calculateBinaryLifting(currentNode, parentNode);
	calculateHeavyLightDecomposition(currentNode, w);

    for (pair<int, int> edge : graph.getConnectedNodes(currentNode)) {
		adjNode = edge.first;
		cost = edge.second;
        if (adjNode != parentNode) {
            depth[adjNode] = depth[currentNode] + 1;
            dfs(depth, graph, adjNode, currentNode, cost);
        }
    }
}

int lca(vector<int>& depth, int u, int v) {
    int result = 0, farthestNode, closestNode;
    farthestNode = depth[u] > depth[v] ? u : v;
    closestNode = depth[u] > depth[v] ? v : u;

    // Find the ancestor of the farthestNode which is at the same level as the closestNode
    for (int i = MAX_LOG_N; i >= 0; i--) {
        int pot = 1 << i; // 2 ^ i
        if (depth[farthestNode] - pot >= depth[closestNode]) {
			result = max(result, hld[farthestNode][i]);
            farthestNode = binaryLifting[farthestNode][i];
        }
    }
 
    if (farthestNode == closestNode) {
        return result;
    }
 
    for (int i = MAX_LOG_N; i >= 0; i--) {
        if (binaryLifting[farthestNode][i] != binaryLifting[closestNode][i]) {
			result = max({result, hld[farthestNode][i], hld[closestNode][i]});
            farthestNode = binaryLifting[farthestNode][i];
            closestNode = binaryLifting[closestNode][i];
        }
    }
 
    return max({result, hld[farthestNode][0], hld[closestNode][0]});
}
 
int main() {
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > minHeap;
	int n, m, u, v, w, index;
	vector<vector<int> > edges;

	cin >> n >> m;

	UnionFind unionFind(n);
	Graph graph(n);
	vector<int> depth(n + 1, 0);
	vector<bool> joined(m, false);
	for(int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
		// Weight must be the first
		minHeap.push({w, i});
	}

	long long mstCost = 0;
	while(!minHeap.empty()) {
		index = minHeap.top().second;
		minHeap.pop();

		u = edges[index][0];
		v = edges[index][1];
		w = edges[index][2];

		if(unionFind.join(u, v)) {
			mstCost += w;
			graph.addEdge(u, v, w);
			joined[index] = true;
		}
	}

	dfs(depth, graph, 1, 0, 0);

	vector<long long> result;
	for(int i = 0; i < m; i++) {
		u = edges[i][0];
		v = edges[i][1];
		w = edges[i][2];
		if(joined[i]) {
			result.push_back(mstCost);
		}
		else {
			result.push_back(mstCost - lca(depth, u, v) + w);
		}
	}
	
	for (int i = 0; i < m; i++) {
		cout << result[i] << endl;
	}

    return 0;
}