#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define V vector<ll>
#define VV vector<V>
#define p push
#define po pop
#define pb push_back
#define ppb pop_back
#define ff first
#define ld long double
#define ss second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
const int m = 1e9 + 7;

void print(ll n)
{
    cout << n << endl;
}

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll lcd(ll a, ll b)
{
    return a * b / gcd(a, b);
}

ll pow(ll x, ll n)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = (res * x) % m;
        n = n >> 1;
        x = (x * x) % m;
    }
    return res;
}

void print4(vector<vector<ll>> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void print3(vector<ll> &v)
{
    for (int j = 0; j < v.size(); j++)
    {
        cout << v[j] << " ";
    }
    cout << endl;
}

void print2(vector<vector<char>> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void print1(vector<string> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    cout << endl;
}

void input(vector<ll> &v, ll n)
{
    for (int i = 0; i < n; i++)
    {
        ll y;
        cin >> y;
        v.pb(y);
    }
}

class disjointset
{
    V rank, parent, rsize;

public:
    disjointset(ll n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1, 0);
        rsize.resize(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    ll findUparent(ll node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = findUparent(parent[node]);
    }

    void unionbyrank(ll u, ll v)
    {
        ll ulp_u = findUparent(u);
        ll ulp_v = findUparent(v);

        if (ulp_u == ulp_v)
            return;

        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_u] > rank[ulp_v])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionbysize(ll u, ll v)
    {
        ll ulp_u = findUparent(u);
        ll ulp_v = findUparent(v);

        if (ulp_u == ulp_v)
            return;

        if (rsize[ulp_u] > rsize[ulp_v])
        {
            rsize[ulp_u] += rsize[ulp_v];
            parent[ulp_v] = ulp_u;
        }
        else
        {
            rsize[ulp_v] += rsize[ulp_u];
            parent[ulp_u] = ulp_v;
        }
    }
};

class segmenttree
{
public:
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    segmenttree(ll size)
    {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    void push(ll idx, ll l, ll r)
    {
        if (lazy[idx] == -1)
            return;

        if (l != r)
        {
            ll mid=(l+r)/2;
            tree[2 * idx] = (mid-l+1)*1LL*lazy[idx];
            tree[2 * idx + 1] = (r-mid)*1LL*lazy[idx];
            lazy[2 * idx] = lazy[idx];
            lazy[2 * idx + 1] = lazy[idx];
        }

        lazy[idx] = -1;
    }

    void build(vector<ll> &arr, ll l, ll r, ll idx)
    {
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }

        ll mid = (l + r) / 2;

        build(arr, l, mid, 2 * idx);
        build(arr, mid + 1, r, 2 * idx + 1);

        tree[idx] = tree[2 * idx]+tree[2 * idx + 1];
    }

    void update(ll idx, ll l, ll r, ll lq, ll rq, ll val)
    {
        push(idx, l, r);

        if (r < lq || l > rq)
            return;

        if (l >= lq && r <= rq)
        {
            tree[idx] = (r-l+1)*1LL*val;
            lazy[idx] = val;
            return;
        }

        ll mid = (l + r) / 2;

        update(2 * idx, l, mid, lq, rq, val);
        update(2 * idx + 1, mid + 1, r, lq, rq, val);

        tree[idx] = tree[2 * idx]+ tree[2 * idx + 1];
    }

    ll query(ll idx, ll l, ll r, ll lq, ll rq)
    {
        push(idx, l, r);

        if (r < lq || l > rq)
            return 0;

        if (l >= lq && r <= rq)
        {
            return tree[idx];
        }

        ll mid = (l + r) / 2;

        ll left_min = query(2 * idx, l, mid, lq, rq);
        ll right_min = query(2 * idx + 1, mid + 1, r, lq, rq);

        return left_min+right_min;
    }

    void build(vector<ll> &arr)
    {
        build(arr, 0, n - 1, 1);
    }

    void update(ll lq, ll rq, ll val)
    {
        update(1, 0, n - 1, lq, rq, val);
    }

    ll query(ll lq, ll rq)
    {
        return query(1, 0, n - 1, lq, rq);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n,m;
    cin>>n>>m;
    vector<ll>arr(n,0);
    segmenttree sg(n);
    sg.build(arr);
    while (m--)
    {
        ll op;
        cin>>op;
        if(op==1){
            ll lq,rq,val;
            cin>>lq>>rq>>val;
            sg.update(lq,rq-1,val);
        }
        else{
            ll lq,rq;
            cin>>lq>>rq;
            cout<<sg.query(lq,rq-1)<<endl;
        }
    }


    return 0;
}