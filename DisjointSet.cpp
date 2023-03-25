class DisjointSet {
    vector<int> rank;
    vector<int> parent;
public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size);

        for(int i = 0; i < size; i++) {
            parent[i] = i;
        }
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
            if(rank[rootx] > rank[rooty])
                parent[rooty] = rootx;
            else if(rank[rootx] < rank[rooty])
                parent[rootx] = rooty;
            else {
                parent[rooty] = rootx;
                rank[rootx]++;
            }
        }
    }
};
