#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define V vector<ll>
#define pb push_back

const ll MOD = 998244353;
const int MAX = 400005;

vector<ll> inv(MAX);

void init()
{
    inv[1] = 1;

    for(int i = 2; i < MAX; i++)
    {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }
}

ll power(ll a, ll b)
{
    ll res = 1;

    while(b)
    {
        if(b & 1)
            res = (res * a) % MOD;

        a = (a * a) % MOD;

        b >>= 1;
    }

    return res;
}

ll ncr(ll n, ll r)
{
    if(r < 0 || r > n)
        return 0;

    r = min(r, n-r);

    ll ans = 1;

    for(ll i = 1; i <= r; i++)
    {
        ans = (ans * ((n-r+i) % MOD)) % MOD;

        ans = (ans * power(i, MOD-2)) % MOD;
    }

    return ans;
}
pair<ll, ll> dfs(ll node,
                 vector<vector<ll>> &adj,
                 vector<ll> &candes,
                 vector<ll> &required)
{
    ll ways = 1;
    ll rem = 0;

    for (auto child : adj[node])
    {
        pair<ll, ll> temp = dfs(child, adj, candes, required);

        // impossible subtree
        if (temp.first == 0)
            return {0, 0};

        ways = (ways * temp.first) % MOD;
        rem += temp.second;
    }

    rem += candes[node];

    if (rem < required[node])
    {
        return {0, 0};
    }

    ll chooseWays = ncr(rem, required[node]);

    ways = (ways * chooseWays) % MOD;

    rem -= required[node];

    return {ways, rem};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    ll n;
    cin >> n;

    vector<vector<ll>> adj(n + 1);

    // parent input for nodes 2 -> n
    for (ll i = 2; i <= n; i++)
    {
        ll parent;
        cin >> parent;

        adj[parent].push_back(i);
    }

    vector<ll> candes(n + 1);
    vector<ll> required(n + 1);

    for (ll i = 1; i <= n; i++)
    {
        cin >> candes[i];
    }

    for (ll i = 1; i <= n; i++)
    {
        cin >> required[i];
    }

    pair<ll, ll> ans = dfs(1, adj, candes, required);

    cout << ans.first << '\n';

    return 0;
}