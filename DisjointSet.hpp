#include <vector>

class DisjointSet {
public:
    DisjointSet(int size) : size(size) {
        parent.resize(size);
        rank.resize(size);

        for(int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        int root = x;
        while(parent[root] != root) {
            root = parent[root];
        }

        while(x != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }

        return root;
    }

    void unify(int x, int y) {
        int px = find(x);
        int py = find(y);

        if(px == py) return;

        if(rank[px] < rank[py]) {
            parent[px] = py;
        } else if(rank[px] < rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }

        numComponents--;
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponentRank(int x) {
        return rank[find(x)];
    }

    int getSize() {
        return parent.size();
    }

    int getNumComponents() {
        return numComponents;
    }

private:
    int size;
    int numComponents;

    std::vector<int> rank;
    std::vector<int> parent;
};