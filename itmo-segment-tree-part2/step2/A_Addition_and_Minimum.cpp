#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Addition and Minimum
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 2, Problem A
 * Description: 
 * Range update: add v to elements from l to r-1.
 * Range query: find the minimum in the range from l to r-1.
 */

typedef long long ll;

class SegmentTree {
public:
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    // Propagates lazy values to children
    void push(ll idx, ll l, ll r) {
        if (lazy[idx] == 0) return;
        if (l != r) {
            tree[2 * idx] += lazy[idx];
            tree[2 * idx + 1] += lazy[idx];
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    // Range addition: adds val to [lq, rq]
    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val) {
        if (r < lq || l > rq) return;
        if (l >= lq && r <= rq) {
            tree[idx] += val;
            lazy[idx] += val;
            return;
        }
        push(idx, l, r);
        ll mid = (l + r) / 2;
        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    // Range minimum query: finds min in [lq, rq]
    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return 1e18; // Neutral element for min
        if (l >= lq && r <= rq) return tree[idx];
        push(idx, l, r);
        ll mid = (l + r) / 2;
        ll left_min = query(2 * idx, l, mid, lq, rq);
        ll right_min = query(2 * idx + 1, mid + 1, r, lq, rq);
        return min(left_min, right_min);
    }

    void update(ll lq, ll rq, ll val) { update(1, 0, n - 1, lq, rq, val); }
    ll query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    SegmentTree st(n);
    
    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) { // Add val to range [l, r-1]
            ll l, r, val;
            cin >> l >> r >> val;
            st.update(l, r - 1, val);
        } else { // Minimum in range [l, r-1]
            ll l, r;
            cin >> l >> r;
            cout << st.query(l, r - 1) << "\n";
        }
    }
    return 0;
}