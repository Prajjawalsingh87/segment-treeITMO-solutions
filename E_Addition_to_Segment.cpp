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
class segmenttree{
  public:
    vector<ll>tree,lazy;
    ll n;
    segmenttree(ll size){
        n=size;
        tree.resize(4*n);
        lazy.resize(4*n);
    }
    void push(ll l,ll r,ll idx){
        tree[idx]+=(r-l+1)*lazy[idx];
        if(l!=r){
            lazy[2*idx]+=lazy[idx];
            lazy[2*idx+1]+=lazy[idx];
        }
        lazy[idx]=0;
    }
    void build(vector<ll>&arr,ll l,ll r,ll idx){
        if(l==r){
            tree[idx]=arr[l];
            lazy[idx]=0;
            return ;
        }
        ll mid=(l+r)/2;
        build(arr,l,mid,2*idx);
        build(arr,mid+1,r,2*idx+1);
        tree[idx]=tree[2*idx]+tree[2*idx+1];
        lazy[idx]=0;
    }
    void update(ll l,ll r,ll idx,ll lq,ll rq,ll val){
        push(l,r,idx);
        if(rq<l || lq>r) return ;
        if(lq<=l && rq>=r){
              lazy[idx]+=val;
              push(l,r,idx);
              return ;
        }
        ll mid=(l+r)/2;
        update(l,mid,2*idx,lq,rq,val);
        update(mid+1,r,2*idx+1,lq,rq,val);
        tree[idx]=tree[2*idx]+tree[2*idx+1];
    }
    ll query(ll idx,ll l,ll r,ll lq,ll rq){
        push(l,r,idx);
        if(l>rq || r<lq) return 0;
        if(l>=lq && r<=rq){
            push(l,r,idx);
            return tree[idx];
        }
        ll mid=(l+r)/2;
        ll left=query(2*idx,l,mid,lq,rq);
        ll right=query(2*idx+1,mid+1,r,lq,rq);
        return left+right;
    }
    void build(vector<ll>&arr){
        build(arr,0,n-1,1);
    }
    void update(ll lq,ll rq,ll val){
        update(0,n-1,1,lq,rq,val);
    }
    ll query(ll lq,ll rq){
        return query(1,0,n-1,lq,rq);
    }
};
int main()
{
    ll n,q;
    cin>>n>>q;
    vector<ll>arr(n,0);
    segmenttree sg(n);
    sg.build(arr);
    while(q--){
       ll val;
       cin>>val;
       if(val==1){
        ll l,r,num;
        cin>>l>>r>>num;
         sg.update(l,r-1,num);
       }
       else{
        ll indx;
        cin>>indx;
          cout<<sg.query(indx,indx)<<endl;
       }
    }
    return 0;
}