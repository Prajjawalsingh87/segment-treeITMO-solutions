#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Inversions
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 3, Problem A
 * Description: 
 * Given a permutation a1, a2, ..., an of numbers from 1 to n.
 * Count for each element ai, how many numbers aj are there such that j < i and aj > ai.
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

    // Point update: set value at pos to val
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

    // Range sum query: sum of elements in [lq, rq]
    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return 0;
        if (l >= lq && r <= rq) return tree[idx];
        ll mid = (l + r) / 2;
        return query(2 * idx, l, mid, lq, rq) + query(2 * idx + 1, mid + 1, r, lq, rq);
    }

    void update(ll pos, ll val) { update(1, 1, n, pos, val); }
    ll query(ll lq, ll rq) { return query(1, 1, n, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    
    SegmentTree st(n);
    for (ll i = 0; i < n; i++) {
        ll val;
        cin >> val;
        // The number of elements seen so far that are greater than val
        // can be found by querying the frequency of elements in range [val+1, n]
        st.update(val, 1);
        cout << st.query(val + 1, n) << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}