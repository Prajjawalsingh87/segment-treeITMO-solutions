#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Segment with the Maximum Sum
 * Description: 
 * Given an array of n integers and m queries of the type (i, v).
 * After each query, you need to update the i-th element of the array to v
 * and find the segment with the maximum sum (the sum of elements in the segment).
 * A segment can be empty, so the maximum sum is at least 0.
 */

typedef long long ll;

struct Node {
    ll sum;           // Sum of all elements in the segment
    ll max_pre_sum;   // Maximum prefix sum
    ll max_suff_sum;  // Maximum suffix sum
    ll ans;           // Maximum segment sum within this range
};

class SegmentTree {
public:
    vector<Node> tree;
    ll n;

    SegmentTree(ll size) {
        n = size;
        tree.resize(4 * n);
    }

    // Merges two nodes to calculate the values for their parent node
    Node combine(Node a, Node b) {
        Node cmb;
        cmb.sum = a.sum + b.sum;
        // Max prefix sum is either a's max prefix or a's total sum + b's max prefix
        cmb.max_pre_sum = max(a.max_pre_sum, a.sum + b.max_pre_sum);
        // Max suffix sum is either b's max suffix or b's total sum + a's max suffix
        cmb.max_suff_sum = max(b.max_suff_sum, b.sum + a.max_suff_sum);
        // Max segment sum is max of (left ans, right ans, cross-mid sum)
        cmb.ans = max({a.ans, b.ans, a.max_suff_sum + b.max_pre_sum});
        return cmb;
    }

    // Builds the segment tree from the initial array
    void build(vector<ll>& arr, ll idx, ll l, ll r) {
        if (l == r) {
            tree[idx].ans = arr[l];
            tree[idx].max_pre_sum = arr[l];
            tree[idx].max_suff_sum = arr[l];
            tree[idx].sum = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    // Updates the element at pos to val and recalculates the path to the root
    void update(ll idx, ll l, ll r, ll pos, ll val) {
        if (pos < l || pos > r) return;
        if (l == r) {
            tree[idx].sum = val;
            tree[idx].ans = val;
            tree[idx].max_pre_sum = val;
            tree[idx].max_suff_sum = val;
            return;
        }
        ll mid = (l + r) / 2;
        if (pos <= mid) update(2 * idx, l, mid, pos, val);
        else update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    // Queries the entire range for the maximum sum
    Node query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) {
            // Return a "neutral" node with very small values except sum
            return {0, (ll)-1e18, (ll)-1e18, (ll)-1e18};
        }
        if (l >= lq && r <= rq) return tree[idx];
        ll mid = (l + r) / 2;
        Node a = query(2 * idx, l, mid, lq, rq);
        Node b = query(2 * idx + 1, mid + 1, r, lq, rq);
        return combine(a, b);
    }

    void build(vector<ll>& arr) { build(arr, 1, 0, n - 1); }
    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    Node query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0); // Fast I/O
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) cin >> arr[i];

    SegmentTree st(n);
    st.build(arr);

    // Maximum sum can be 0 if all elements on chosen segment are negative/empty
    cout << max(st.query(0, n - 1).ans, 0LL) << "\n";

    while (q--) {
        ll pos, val;
        cin >> pos >> val;
        st.update(pos, val);
        cout << max(st.query(0, n - 1).ans, 0LL) << "\n";
    }

    return 0;
}