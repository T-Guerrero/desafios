#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

class UnionFind {
    private:
        vector<int> parent;
        vector<int> componentSize;
    public:
        UnionFind(int n) {
            for (int i = 0; i < n; i++) {
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

        void join(int vertex1, int vertex2) {
            int rep1 = find(vertex1);
            int rep2 = find(vertex2);

            if (rep1 == rep2) return;

            // Optimization
            if (componentSize[rep1] > componentSize[rep2]) {
                parent[rep2] = rep1;
                componentSize[rep1] += componentSize[rep2];
            } else {
                parent[rep1] = rep2;
                componentSize[rep2] += componentSize[rep1];
            }
        }
};

int main() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > minHeap;
    int n, m, u, v, w, index, counter;
    long long mstCost;

    cin >> n >> m;

    while(n > 0) {
        UnionFind unionFind(n);
        vector<vector<int> > edges;
        vector<pair<int, int> > result;

        mstCost = counter = 0;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            // Weight must be the first
            minHeap.push({w, i});
        }

        while(!minHeap.empty()) {
            index = minHeap.top().second;
            minHeap.pop();

            u = edges[index][0];
            v = edges[index][1];
            w = edges[index][2];

            if (unionFind.find(u) != unionFind.find(v)) {
                unionFind.join(u, v);
                mstCost += w;
                counter++;
                result.push_back({min(u, v), max(u, v)});
            }
        }

        if (counter != n - 1) {
            cout << "Impossible" << endl;
        } else {
            sort(result.begin(), result.end());
            cout << mstCost << endl;
            for (int i = 0; i < counter; i++) {
                cout << result[i].first << " " << result[i].second << endl;
            }
        }

        cin >> n >> m;
    }

    return 0;
}