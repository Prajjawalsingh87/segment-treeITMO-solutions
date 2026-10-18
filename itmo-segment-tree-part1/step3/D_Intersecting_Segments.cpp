#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Intersecting Segments
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 3, Problem D
 * Description: 
 * Given 2n points representing n segments [li, ri].
 * Each segment occurs twice. For each segment, count how many segments intersect it.
 * Intersection means one endpoint is inside and one is outside.
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

    void update(ll pos, ll val) { update(1, 0, 2 * n - 1, pos, val); }
    ll query(ll lq, ll rq) { return query(1, 0, 2 * n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    
    vector<ll> arr(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> arr[i];

    vector<ll> l_pos(n + 1, -1);
    vector<ll> ans(n + 1, 0);
    
    auto solve = [&]() {
        SegmentTree st(2 * n);
        l_pos.assign(n + 1, -1);
        for (int i = 0; i < 2 * n; i++) {
            ll val = arr[i];
            if (l_pos[val] == -1) {
                l_pos[val] = i;
                st.update(i, 1);
            } else {
                st.update(l_pos[val], 0);
                ans[val] += st.query(l_pos[val], i);
            }
        }
    };

    solve();
    reverse(arr.begin(), arr.end());
    solve();

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
    return 0;
}