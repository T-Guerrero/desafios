#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007
#define RED 0
#define BLACK 1

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

        long long dfs(vector<bool>& visited, int vertex) {
            visited[vertex] = true;

            long long count = 1;
            for (int neighbor : getConnectedNodes(vertex)) {
                if (!visited[neighbor]) {
                    count += dfs(visited, neighbor);
                }
            }

            return count;
        }
};

long long recursiveExponentiation(long long number, long long expoent) {
    if (expoent == 0)
        return 1;

    if (expoent % 2 == 0) {
        long long subResult = recursiveExponentiation(number, expoent/2);
        return (subResult % MOD * subResult % MOD) % MOD;
    } else {
        return (recursiveExponentiation(number, expoent - 1) * (number % MOD)) % MOD;
    }
}

int main() {
    long long n, k, u, v, x, count, result;

    cin >> n >> k;

    Graph graph(n);
    vector<bool> visited(n + 1, false);
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v >> x;
        if (x == RED) {
            graph.addEdge(u, v);
        }
    }

    result = recursiveExponentiation(n, k);
    for (int i = 1; i <= n; i++) {
        if(!visited[i]) {
            count = graph.dfs(visited, i);
            result = (result - recursiveExponentiation(count, k) + MOD) % MOD;
        }
    }

    cout << result << endl;
    return 0;
}