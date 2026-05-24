#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Sign alternation
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 4, Problem A
 * Description: 
 * Range update: change element at position i to v.
 * Range query: calculate the sum ai - ai+1 + ai+2 - ai+3 + ... + (-1)^(r-l) * ar.
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
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return 0;
        if (l >= lq && r <= rq) return tree[idx];
        ll mid = (l + r) / 2;
        return query(2 * idx, l, mid, lq, rq) + query(2 * idx + 1, mid + 1, r, lq, rq);
    }

    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    
    // We use two segment trees to store elements at even and odd indices separately.
    // For a sum with alternating signs starting at l:
    // If l is even: (sum of elements at even indices) - (sum of elements at odd indices)
    // If l is odd: (sum of elements at odd indices) - (sum of elements at even indices)
    SegmentTree st_even(n), st_odd(n);
    
    for (ll i = 0; i < n; i++) {
        ll val;
        cin >> val;
        if (i % 2 == 0) st_even.update(i, val);
        else st_odd.update(i, val);
    }
    
    ll q;
    cin >> q;
    while (q--) {
        ll op;
        cin >> op;
        if (op == 0) { // Update
            ll idx, val;
            cin >> idx >> val;
            idx--; // convert to 0-indexed
            if (idx % 2 == 0) st_even.update(idx, val);
            else st_odd.update(idx, val);
        } else { // Query
            ll l, r;
            cin >> l >> r;
            l--; r--; // convert to 0-indexed
            if (l % 2 == 0) {
                cout << st_even.query(l, r) - st_odd.query(l, r) << "\n";
            } else {
                cout << st_odd.query(l, r) - st_even.query(l, r) << "\n";
            }
        }
    }
    return 0;
}