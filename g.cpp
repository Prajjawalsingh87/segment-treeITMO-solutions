#include <bits/stdc++.h>
using namespace std;
 
class SegmentTree {
    vector<int> tree;
    int n;
 
public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, INT_MAX);
    }
 
    void build(vector<int>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }
 
    void update(int idx, int l, int r, int pos, int val) {
        if (pos < l || pos > r) return;
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(2 * idx, l, mid, pos, val);
        update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }
 
    int query(int idx, int l, int r, int lq, int rq) {
        if (lq > r || l > rq) return INT_MAX;
        if (lq <= l && rq >= r) return tree[idx];
        int mid = (l + r) / 2;
        int leftQuery = query(2 * idx, l, mid, lq, rq);
        int rightQuery = query(2 * idx + 1, mid + 1, r, lq, rq);
        return min(leftQuery, rightQuery);
    }
 
    void build(vector<int>& arr) {
        build(arr, 1, 0, n - 1);
    }
 
    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }
 
    int query(int lq, int rq) {
        return query(1, 0, n - 1, lq, rq);
    }
};
 
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
 
    SegmentTree segTree(n);
    segTree.build(arr);
 
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << segTree.query(l, r) << endl;
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
