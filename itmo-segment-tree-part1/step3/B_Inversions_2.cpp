#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Inversions 2
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 3, Problem B
 * Description: 
 * Given an array of inversions. For each element, the number of elements to its left that are greater.
 * Find the original permutation.
 * Logic: Process from right to left, find the (k+1)-th largest available number using a segment tree.
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

    void build(ll idx, ll l, ll r) {
        if (l == r) {
            tree[idx] = 1; // Initially all numbers are available
            return;
        }
        ll mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    // Update: set availability of pos to val (0 or 1)
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

    // Find the k-th available number from the right
    ll find_kth(ll idx, ll l, ll r, ll k) {
        if (l == r) return l;
        ll mid = (l + r) / 2;
        // Number of available elements in the right child
        ll right_count = tree[2 * idx + 1];
        if (right_count >= k) return find_kth(2 * idx + 1, mid + 1, r, k);
        else return find_kth(2 * idx, l, mid, k - right_count);
    }

    void build() { build(1, 1, n); }
    void update(ll pos, ll val) { update(1, 1, n, pos, val); }
    ll find_kth(ll k) { return find_kth(1, 1, n, k); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];

    SegmentTree st(n);
    st.build();

    vector<ll> ans;
    // Process from right to left
    for (ll i = n - 1; i >= 0; i--) {
        // b[i] is the number of elements to the left that are greater.
        // In the current available set, we want the (b[i]+1)-th largest element.
        ll val = st.find_kth(b[i] + 1);
        ans.push_back(val);
        st.update(val, 0); // Number is no longer available
    }

    reverse(ans.begin(), ans.end());
    for (ll i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}