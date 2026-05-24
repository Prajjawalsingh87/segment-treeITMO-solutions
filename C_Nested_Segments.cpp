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
    ll findUparent(ll node){
        if(parent[node]==node) return node;
        return parent[node]=findUparent(parent[node]);
    }
    void unionbyrank(ll u,ll v){
        ll ulp_u=findUparent(u);
        ll ulp_v=findUparent(v);
        if(ulp_u==ulp_v) return;
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }
        else if(rank[ulp_u]>rank[ulp_v]){
            parent[ulp_v]=ulp_u;
        }
        else{
            parent[ulp_v]=ulp_u;
            rank[ulp_u]++;
        }
    }
    void unionbysize(ll u,ll v){
        ll ulp_u=findUparent(u);
        ll ulp_v=findUparent(v);
        if(ulp_u==ulp_v) return;
        if(rsize[ulp_u]>rsize[ulp_v]){
            rsize[ulp_u]+=rsize[ulp_v];
            parent[ulp_v]=ulp_u;
        }
        else{
             rsize[ulp_v]+=rsize[ulp_u];
            parent[ulp_u]=ulp_v;
        }
    }
};
class segementTree{
    public:
    vector<pair<ll,ll>>tree;
    ll n;
    segementTree(ll size){
        n=size;
        tree.resize(4*n);
    }
    void build(ll idx,ll l,ll r,vector<ll>&arr){
         if(l==r){
             tree[idx]={0,0};
             return ;
         }
         ll mid=(l+r)/2;
         build(2*idx,l,mid,arr);
         build(2*idx+1,mid+1,r,arr);
         tree[idx].first=tree[2*idx].first+tree[2*idx+1].first;
         tree[idx].second=tree[2*idx].second+tree[2*idx+1].second;
    }
    void update(ll idx,ll l,ll r,ll pos,ll val,ll is_l){
        if(pos<l || pos>r) return;
        if(l==r){
            if(is_l){
                tree[idx].first=1;
            }
            else{
                tree[idx].second=1;
            }
            return ;
        }
        ll mid=(l+r)/2;
        if(pos<=mid) update(2*idx,l,mid,pos,val,is_l);
        else update(2*idx+1,mid+1,r,pos,val,is_l);
        tree[idx].first=tree[2*idx].first+tree[2*idx+1].first;
        tree[idx].second=tree[2*idx].second+tree[2*idx+1].second;
    }
    pair<ll,ll> query(ll idx,ll l,ll r,ll lq,ll rq){
        if(l>rq || r< lq) return {0,0};
        if(l>=lq && r<=rq) return tree[idx];
        ll mid=(l+r)/2;
        pair<ll,ll>left_child=query(2*idx,l,mid,lq,rq);
        pair<ll,ll>right_child=query(2*idx+1,mid+1,r,lq,rq);
        return {left_child.first+right_child.first,left_child.second+right_child.second};
    }
    void build(vector<ll>&arr){
        build(1,0,n-1,arr);
    }
    void update(ll pos,ll val,ll is_l){
        update(1,0,n-1,pos,val,is_l);
    }
    pair<ll,ll> query(ll lq,ll rq){
        return query(1,0,n-1,lq,rq);
    }

};
int main()
{
    ll n;
    cin>>n;
    vector<ll>arr;
    vector<ll>ans(n,0);
    for(ll i=0;i<2*n;i++){
       ll num;
       cin>>num;
       arr.push_back(num);
    }
    map<ll,ll>mp;
    segementTree sg(2*n);
    sg.build(arr);
    for(ll i=0;i<2*n;i++){
        if(mp.find(arr[i])!=mp.end()){

            ll last_indx=mp[arr[i]];

            pair<ll,ll>middle_counts=
                sg.query(last_indx+1,i-1);

            ans[arr[i]]=middle_counts.first;

            sg.update(last_indx,1,1);
      }
        else{
             mp[arr[i]]=i;
        }
    }
    for(ll i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}