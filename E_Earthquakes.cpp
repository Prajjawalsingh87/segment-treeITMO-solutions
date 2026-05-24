#include <bits/stdc++.h>
using namespace std;

#define ll long long

class segmenttree {
public:

    vector<ll> mn;
    vector<ll> mx;
    vector<ll> cnt;
    vector<ll> lazy;

    ll n;

    segmenttree(ll size) {

        n = size;

        mn.resize(4 * n, 1e18);
        mx.resize(4 * n, -1e18);
        cnt.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void build(ll idx, ll l, ll r) {

        if (l == r) {

            mn[idx] = 1e18;
            mx[idx] = -1e18;
            cnt[idx] = 0;

            return;
        }

        ll mid = (l + r) / 2;

        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);

        mn[idx] = 1e18;
        mx[idx] = -1e18;
        cnt[idx] = 0;
    }

    void push(ll idx) {

        if (!lazy[idx]) return;

        mn[2 * idx] = 1e18;
        mx[2 * idx] = -1e18;

        mn[2 * idx + 1] = 1e18;
        mx[2 * idx + 1] = -1e18;

        cnt[2 * idx] = 0;
        cnt[2 * idx + 1] = 0;

        lazy[2 * idx] = 1;
        lazy[2 * idx + 1] = 1;

        lazy[idx] = 0;
    }

    void merge(ll idx) {

        mn[idx] = min(mn[2 * idx], mn[2 * idx + 1]);

        mx[idx] = max(mx[2 * idx], mx[2 * idx + 1]);

        cnt[idx] = cnt[2 * idx] + cnt[2 * idx + 1];
    }

    void update(ll idx, ll l, ll r, ll pos, ll val) {

        if (l == r) {

            mn[idx] = val;
            mx[idx] = val;
            cnt[idx] = 1;
            lazy[idx] = 0;

            return;
        }

        push(idx);

        ll mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * idx, l, mid, pos, val);
        else
            update(2 * idx + 1, mid + 1, r, pos, val);

        merge(idx);
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq, ll val) {

        if (r < lq || l > rq || cnt[idx] == 0)
            return 0;

        // all elements > val
        if (mn[idx] > val)
            return 0;

        // all elements <= val
        if (lq <= l && r <= rq && mx[idx] <= val) {

            ll ans = cnt[idx];

            mn[idx] = 1e18;
            mx[idx] = -1e18;

            cnt[idx] = 0;

            lazy[idx] = 1;

            return ans;
        }

        if (l == r) {

            if (mn[idx] <= val) {

                mn[idx] = 1e18;
                mx[idx] = -1e18;

                cnt[idx] = 0;

                return 1;
            }

            return 0;
        }

        push(idx);

        ll mid = (l + r) / 2;

        ll left = query(2 * idx, l, mid, lq, rq, val);

        ll right = query(2 * idx + 1, mid + 1, r, lq, rq, val);

        merge(idx);

        return left + right;
    }

    void build() {

        build(1, 0, n - 1);
    }

    void update(ll pos, ll val) {

        update(1, 0, n - 1, pos, val);
    }

    ll query(ll l, ll r, ll val) {

        return query(1, 0, n - 1, l, r, val);
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    segmenttree sg(n);

    sg.build();

    while (q--) {

        ll op;
        cin >> op;

        if (op == 1) {

            ll pos, val;
            cin >> pos >> val;

            sg.update(pos, val);
        }
        else {

            ll l, r, val;
            cin >> l >> r >> val;

            cout << sg.query(l, r - 1, val) << '\n';
        }
    }

    return 0;
}