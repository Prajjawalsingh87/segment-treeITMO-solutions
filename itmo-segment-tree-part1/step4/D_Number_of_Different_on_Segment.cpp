#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Number of Different on Segment
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 4, Problem D
 * Description: 
 * Range update: ai = x.
 * Range query: number of distinct elements in a[l...r].
 * Values are small (1 to 40). Uses bitmasks.
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
            tree[idx] = (1LL << arr[l]);
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = (tree[2 * idx] | tree[2 * idx + 1]);
    }

    void update(ll idx, ll l, ll r, ll pos, ll val) {
        if (l == r) {
            tree[idx] = (1LL << val);
            return;
        }
        ll mid = (l + r) / 2;
        if (pos <= mid) update(2 * idx, l, mid, pos, val);
        else update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = (tree[2 * idx] | tree[2 * idx + 1]);
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return 0;
        if (l >= lq && r <= rq) return tree[idx];
        ll mid = (l + r) / 2;
        return (query(2 * idx, l, mid, lq, rq) | query(2 * idx + 1, mid + 1, r, lq, rq));
    }

    void build(const vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
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
        ll op, x, y;
        cin >> op >> x >> y;
        if (op == 1) { // Query distinct
            cout << __builtin_popcountll(st.query(x - 1, y - 1)) << "\n";
        } else { // Point update
            st.update(x - 1, y);
        }
    }
    return 0;
}