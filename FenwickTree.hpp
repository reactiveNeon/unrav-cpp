#include <cstddef>
#include <vector>

class FenwickTree {
    std::vector<int> bit; // binary indexed tree
    int n;

    FenwickTree(int size) : n(size) {
        bit.assign(n, 0);
    }

    FenwickTree(std::vector<int> const &v) : FenwickTree(v.size()) {
        for(size_t i = 0; i < v.size(); i++) {
            add(i, v[i]);
        } 
    }

    int sum(int r) {
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1) {
            ret += bit[r];
        }
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1)) {
            bit[idx] += delta;
        }
    }
};