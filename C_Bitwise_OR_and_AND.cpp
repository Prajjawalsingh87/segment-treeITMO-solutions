#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Bitwise OR and AND
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 2, Problem C
 * Description: 
 * Range update: ai = ai | v for all l <= i < r.
 * Range query: calculate the bitwise AND of ai in the range [l, r).
 */

typedef long long ll;

class SegmentTree {
public:
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(ll idx, ll l, ll r) {
        if (lazy[idx] == 0) return;
        if (l != r) {
            tree[2 * idx] |= lazy[idx];
            tree[2 * idx + 1] |= lazy[idx];
            lazy[2 * idx] |= lazy[idx];
            lazy[2 * idx + 1] |= lazy[idx];
        }
        lazy[idx] = 0;
    }

    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val) {
        if (r < lq || l > rq) return;
        if (l >= lq && r <= rq) {
            tree[idx] |= val;
            lazy[idx] |= val;
            return;
        }
        push(idx, l, r);
        ll mid = (l + r) / 2;
        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);
        tree[idx] = (tree[2 * idx] & tree[2 * idx + 1]);
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return (1LL << 31) - 1; // Return all 1s for AND identity
        if (l >= lq && r <= rq) return tree[idx];
        push(idx, l, r);
        ll mid = (l + r) / 2;
        return (query(2 * idx, l, mid, lq, rq) & query(2 * idx + 1, mid + 1, r, lq, rq));
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
        if (op == 1) { // Range OR
            ll l, r, v;
            cin >> l >> r >> v;
            st.update(l, r - 1, v);
        } else { // Range AND
            ll l, r;
            cin >> l >> r;
            cout << st.query(l, r - 1) << "\n";
        }
    }
    return 0;
}