#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: K-th one
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 2, Problem B
 * Description: 
 * Range update: flip element at position i (0 to 1 or 1 to 0).
 * Range query: find the index of the k-th one (0-indexed).
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
            tree[idx] = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
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

    // Direct search for k-th one in the tree
    ll find_kth(ll idx, ll l, ll r, ll k) {
        if (l == r) return l;
        ll mid = (l + r) / 2;
        if (tree[2 * idx] > k) return find_kth(2 * idx, l, mid, k);
        else return find_kth(2 * idx + 1, mid + 1, r, k - tree[2 * idx]);
    }

    void build(const vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll find_kth(ll k) { return find_kth(1, 0, n - 1, k); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(n);
    st.build(arr);

    while (q--) {
        ll op, val;
        cin >> op >> val;
        if (op == 1) { // Flip element at position val
            arr[val] = 1 - arr[val];
            st.update(val, arr[val]);
        } else { // Find (val+1)-th one
            cout << st.find_kth(val) << "\n";
        }
    }
    return 0;
}