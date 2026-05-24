#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: First element at least X - 2
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 3, Problem B (variant)
 * Description: 
 * Range query: find the first index i >= l such that ai >= x.
 * Point update: change ai to v.
 * Optimized with tree traversal.
 */

typedef long long ll;

class SegmentTree {
public:
    vector<ll> tree;
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    void build(const vector<ll>& arr, ll idx, ll l, ll r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }

    void update(ll idx, ll l, ll r, ll pos, ll val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        ll mid = (l + r) / 2;
        if (pos <= mid) update(2 * idx, l, mid, pos, val);
        else update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll find_first(ll idx, ll l, ll r, ll lq, ll val) {
        if (tree[idx] < val || r < lq) return -1;
        if (l == r) return l;
        ll mid = (l + r) / 2;
        ll res = find_first(2 * idx, l, mid, lq, val);
        if (res == -1) res = find_first(2 * idx + 1, mid + 1, r, lq, val);
        return res;
    }

    void build(const vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll find_first(ll lq, ll val) { return find_first(1, 0, n - 1, lq, val); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(n);
    st.build(arr);

    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) { // Point update
            ll pos, val;
            cin >> pos >> val;
            st.update(pos, val);
        } else { // Find first i >= l such that ai >= val
            ll val, l;
            cin >> val >> l;
            cout << st.find_first(l, val) << "\n";
        }
    }
    return 0;
}