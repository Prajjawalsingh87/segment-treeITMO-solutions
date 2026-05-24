#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Select from Subtrees
 * Description: 
 * DP on trees with combinatorics. Counts ways to select required items from subtrees.
 */

typedef long long ll;
const int MOD = 998244353;
const int MAX = 400005;

ll power(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll n) { return power(n, MOD - 2); }

ll ncr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    ll num = 1, den = 1;
    for (ll i = 1; i <= r; i++) {
        num = (num * (n - i + 1)) % MOD;
        den = (den * i) % MOD;
    }
    return (num * modInverse(den)) % MOD;
}

pair<ll, ll> dfs(int u, const vector<vector<int>>& adj, const vector<ll>& cand, const vector<ll>& req) {
    ll total_ways = 1;
    ll available = cand[u];
    for (int v : adj[u]) {
        auto res = dfs(v, adj, cand, req);
        if (res.first == 0) return {0, 0};
        total_ways = (total_ways * res.first) % MOD;
        available += res.second;
    }
    if (available < req[u]) return {0, 0};
    total_ways = (total_ways * ncr(available, req[u])) % MOD;
    return {total_ways, available - req[u]};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    if (!(cin >> n)) return 0;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    vector<ll> cand(n + 1), req(n + 1);
    for (int i = 1; i <= n; i++) cin >> cand[i];
    for (int i = 1; i <= n; i++) cin >> req[i];

    auto ans = dfs(1, adj, cand, req);
    cout << ans.first << "\n";
    return 0;
}