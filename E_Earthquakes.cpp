#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Earthquakes
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 2, Problem E (variant)
 * Description: 
 * Range update: buildings in pos p get strength val.
 * Range query: count buildings in range [l, r) with strength <= val and destroy them.
 */

typedef long long ll;

class SegmentTree {
public:
    vector<ll> tree; // Min strength in range
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.assign(4 * n, 2e18);
    }

    void update(ll idx, ll l, ll r, ll pos, ll val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        ll mid = (l + r) / 2;
        if (pos <= mid) update(2 * idx, l, mid, pos, val);
        else update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query_and_destroy(ll idx, ll l, ll r, ll lq, ll rq, ll p) {
        if (r < lq || l > rq || tree[idx] > p) return 0;
        if (l == r) {
            tree[idx] = 2e18; // Destroyed
            return 1;
        }
        ll mid = (l + r) / 2;
        ll res = query_and_destroy(2 * idx, l, mid, lq, rq, p);
        res += query_and_destroy(2 * idx + 1, mid + 1, r, lq, rq, p);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
        return res;
    }

    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query_and_destroy(ll lq, ll rq, ll p) { return query_and_destroy(1, 0, n - 1, lq, rq, p); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    SegmentTree st(n);
    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) { // Add building
            ll i, h;
            cin >> i >> h;
            st.update(i, h);
        } else { // Earthquake
            ll l, r, p;
            cin >> l >> r >> p;
            cout << st.query_and_destroy(l, r - 1, p) << "\n";
        }
    }
    return 0;
}