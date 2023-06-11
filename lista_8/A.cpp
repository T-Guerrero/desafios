#include <iostream>
#include <vector>
using namespace std;

#define JOIN_OPERATION 0
#define FIND_OPERATION 1

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
    int n, q, operation, u, v, rep1, rep2;

    // fast read
	ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> q;

    vector<int>parent(n), size(n);
    UnionFind unionFind(n);

    for (int i = 0; i < q; i++) {
        cin >> operation >> u >> v;
        switch(operation) {
            case JOIN_OPERATION:
                unionFind.join(u, v);
                break;
            case FIND_OPERATION:
                rep1 = unionFind.find(u);
                rep2 = unionFind.find(v);
                cout << (rep1 == rep2) << endl;
                break;
        }
    }

    return 0;
}