#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: List Removals
 * Source: CSES
 * Description: 
 * You are given a list of n integers. Your task is to process q queries:
 * find and remove the element at the i-th position in the current list.
 * Optimized with Segment Tree traversal.
 */

typedef long long ll;

class SegmentTree {
public:
    vector<int> tree;
    int n;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    int find_and_remove(int idx, int l, int r, int k) {
        if (l == r) {
            tree[idx] = 0;
            return l;
        }
        int mid = (l + r) / 2;
        int res;
        if (k <= tree[2 * idx]) res = find_and_remove(2 * idx, l, mid, k);
        else res = find_and_remove(2 * idx + 1, mid + 1, r, k - tree[2 * idx]);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        return res;
    }

    void build() { build(1, 0, n - 1); }
    int find_and_remove(int k) { return find_and_remove(1, 0, n - 1, k); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    if (!(cin >> n)) return 0;
    
    vector<ll> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    SegmentTree st(n);
    st.build();

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        int idx = st.find_and_remove(p);
        cout << x[idx] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}