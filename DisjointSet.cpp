class DisjointSet {
    vector<int> parent;
    vector<int> rank;
public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size);
    }

    int findLeader(int x) {
        if(parent[x] == x)
            return x;
        
        return findLeader(parent[x]);
    }

    void makeUnion(int x, int y) {
        int rootx = findLeader(x);
        int rooty = findLeader(y);

        if(rootx != rooty) {
            if(rank[x] > rank[y])
                parent[y] = x;
            else if(rank[x] < rank[y])
                parent[x] = y;
            else {
                parent[x] = y;
                rank[y]++;
            }
        }
    }
};
