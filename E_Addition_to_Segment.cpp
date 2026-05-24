#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Addition to Segment
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 2, Problem E
 * Description: 
 * Range update: ai = ai + v for all l <= i < r.
 * Point query: find the value of ai.
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

    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val) {
        if (r < lq || l > rq) return;
        if (l >= lq && r <= rq) {
            tree[idx] += val;
            return;
        }
        ll mid = (l + r) / 2;
        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);
    }

    ll query(ll idx, ll l, ll r, ll pos) {
        if (l == r) return tree[idx];
        ll mid = (l + r) / 2;
        if (pos <= mid) return tree[idx] + query(2 * idx, l, mid, pos);
        else return tree[idx] + query(2 * idx + 1, mid + 1, r, pos);
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
        ll type;
        cin >> type;
        if (type == 1) { // Range addition
            ll l, r, v;
            cin >> l >> r >> v;
            st.update(l, r - 1, v);
        } else { // Point query
            ll i;
            cin >> i;
            cout << st.query(i) << "\n";
        }
    }
    return 0;
}