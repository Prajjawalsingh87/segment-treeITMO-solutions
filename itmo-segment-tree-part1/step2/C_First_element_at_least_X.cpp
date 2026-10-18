#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: First element at least X
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 2, Problem C
 * Description: 
 * Range update: change element at position i to v.
 * Range query: find the smallest index i such that ai >= x.
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

    // Find the first index i in [l, r] such that tree[idx] >= x
    ll find_first(ll idx, ll l, ll r, ll x) {
        if (tree[idx] < x) return -1;
        if (l == r) return l;
        ll mid = (l + r) / 2;
        ll res = find_first(2 * idx, l, mid, x);
        if (res == -1) res = find_first(2 * idx + 1, mid + 1, r, x);
        return res;
    }

    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll find_first(ll x) { return find_first(1, 0, n - 1, x); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    SegmentTree st(n);
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
        st.update(i, arr[i]);
    }

    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) { // Point update
            ll i, v;
            cin >> i >> v;
            st.update(i, v);
        } else { // Find first index
            ll x;
            cin >> x;
            cout << st.find_first(x) << "\n";
        }
    }
    return 0;
}