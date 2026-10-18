#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Cryptography
 * Source: ITMO Academy Pilot, Segment Tree 1, Step 4, Problem B
 * Description: 
 * Perform matrix multiplication in a given range modulo r.
 * The matrices are 2x2. Multiplication is not commutative.
 */

typedef long long ll;

struct Matrix {
    ll a11, a12, a21, a22;
    Matrix() {
        a11 = 1; a12 = 0;
        a21 = 0; a22 = 1; // Identity matrix
    }
};

class SegmentTree {
public:
    vector<Matrix> tree;
    ll n, mod;

    SegmentTree(ll _n, ll _mod) {
        n = _n;
        mod = _mod;
        tree.resize(4 * n);
    }

    // Matrix multiplication modulo mod
    Matrix combine(const Matrix& a, const Matrix& b) {
        Matrix res;
        res.a11 = (a.a11 * b.a11 + a.a12 * b.a21) % mod;
        res.a12 = (a.a11 * b.a12 + a.a12 * b.a22) % mod;
        res.a21 = (a.a21 * b.a11 + a.a22 * b.a21) % mod;
        res.a22 = (a.a21 * b.a12 + a.a22 * b.a22) % mod;
        return res;
    }

    void build(const vector<Matrix>& arr, ll idx, ll l, ll r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(arr, 2 * idx, l, mid);
        build(arr, 2 * idx + 1, mid + 1, r);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    Matrix query(ll idx, ll l, ll r, ll lq, ll rq) {
        if (r < lq || l > rq) return Matrix(); // Return identity
        if (l >= lq && r <= rq) return tree[idx];
        ll mid = (l + r) / 2;
        Matrix left = query(2 * idx, l, mid, lq, rq);
        Matrix right = query(2 * idx + 1, mid + 1, r, lq, rq);
        return combine(left, right);
    }

    void build(const vector<Matrix>& arr) { build(arr, 1, 0, n - 1); }
    Matrix query(ll lq, ll rq) { return query(1, 0, n - 1, lq, rq); }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll r, n, m;
    if (!(cin >> r >> n >> m)) return 0;
    
    vector<Matrix> arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i].a11 >> arr[i].a12;
        cin >> arr[i].a21 >> arr[i].a22;
    }

    SegmentTree st(n, r);
    st.build(arr);

    while (m--) {
        ll left, right;
        cin >> left >> right;
        left--; right--;
        Matrix res = st.query(left, right);
        cout << res.a11 << " " << res.a12 << "\n";
        cout << res.a21 << " " << res.a22 << "\n\n";
    }
    return 0;
}