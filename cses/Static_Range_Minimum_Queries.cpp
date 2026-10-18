#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Static Range Minimum Queries
 * Source: CSES
 * Description: 
 * Range query: calculate the minimum element in range [l, r].
 */

typedef long long ll;

class SegmentTree {
public:
    vector<ll> tree;
    int n;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 2e18);
    }

    void build(const vector<ll>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int idx, int l, int r, int lq, int rq) {
        if (r < lq || l > rq) return 2e18;
        if (l >= lq && r <= rq) return tree[idx];
        int mid = (l + r) / 2;
        return min(query(2 * idx, l, mid, lq, rq), query(2 * idx + 1, mid + 1, r, lq, rq));
    }

    void build(const vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(n);
    st.build(arr);

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l - 1, r - 1) << "\n";
    }
    return 0;
}