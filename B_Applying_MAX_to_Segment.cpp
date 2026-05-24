#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Applying MAX to Segment
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 1, Problem B
 * Description: 
 * Range update: ai = max(ai, v) for all l <= i < r.
 * Point query: find the value of the element at position i.
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

    // Range update: ai = max(ai, val) for l <= i <= r
    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val) {
        if (r < lq || l > rq) return;
        if (l >= lq && r <= rq) {
            tree[idx] = max(tree[idx], val);
            return;
        }
        ll mid = (l + r) / 2;
        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);
    }

    // Point query: find the value at position pos
    // The value is the maximum of all values applied to segments containing pos
    ll query(ll idx, ll l, ll r, ll pos) {
        if (l == r) return tree[idx];
        ll mid = (l + r) / 2;
        ll res = tree[idx];
        if (pos <= mid) res = max(res, query(2 * idx, l, mid, pos));
        else res = max(res, query(2 * idx + 1, mid + 1, r, pos));
        return res;
    }

    void update(ll lq, ll rq, ll val) { update(1, 0, n - 1, lq, rq, val); }
    ll query(ll pos) { return query(1, 0, n - 1, pos); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    SegmentTree st(n);
    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) { // Range MAX update
            ll l, r, val;
            cin >> l >> r >> val;
            st.update(l, r - 1, val);
        } else { // Point query
            ll pos;
            cin >> pos;
            cout << st.query(pos) << "\n";
        }
    }
    return 0;
}