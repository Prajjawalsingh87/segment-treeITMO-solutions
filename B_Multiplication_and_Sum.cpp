#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Multiplication and Sum
 * Source: ITMO Academy Pilot, Segment Tree 2, Step 2, Problem B
 * Description: 
 * Range update: ai = ai * v mod 10^9 + 7 for all l <= i < r.
 * Range query: calculate the sum ai mod 10^9 + 7 for all l <= i < r.
 */

typedef long long ll;
const int MOD = 1e9 + 7;

class SegmentTree {
public:
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 1);
    }

    void push(ll idx, ll l, ll r) {
        if (lazy[idx] == 1) return;
        if (l != r) {
            lazy[2 * idx] = (lazy[2 * idx] * lazy[idx]) % MOD;
            lazy[2 * idx + 1] = (lazy[2 * idx + 1] * lazy[idx]) % MOD;
            tree[2 * idx] = (tree[2 * idx] * lazy[idx]) % MOD;
            tree[2 * idx + 1] = (tree[2 * idx + 1] * lazy[idx]) % MOD;
        }
        lazy[idx] = 1;
    }

    void build(const vector<ll>& arr, ll idx, ll l, ll r) {
        if (l == r) {
            tree[idx] = arr[l] % MOD;
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = (tree[2 * idx] + tree[2 * idx + 1]) % MOD;
    }

    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val) {
        if (r < lq || l > rq) return;
        if (l >= lq && r <= rq) {
            tree[idx] = (tree[idx] * val) % MOD;
            lazy[idx] = (lazy[idx] * val) % MOD;
            return;
        }
        push(idx, l, r);
        ll mid = (l + r) / 2;
        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);
        tree[idx] = (tree[2 * idx] + tree[2 * idx + 1]) % MOD;
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return 0;
        if (l >= lq && r <= rq) return tree[idx];
        push(idx, l, r);
        ll mid = (l + r) / 2;
        return (query(2 * idx, l, mid, lq, rq) + query(2 * idx + 1, mid + 1, r, lq, rq)) % MOD;
    }

    void build(const vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    void update(ll lq, ll rq, ll val) { update(1, 0, n - 1, lq, rq, val); }
    ll query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> arr(n, 1);
    SegmentTree st(n);
    st.build(arr);

    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) { // Range multiply
            ll l, r, v;
            cin >> l >> r >> v;
            st.update(l, r - 1, v);
        } else { // Range sum
            ll l, r;
            cin >> l >> r;
            cout << st.query(l, r - 1) << "\n";
        }
    }
    return 0;
}