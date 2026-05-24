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
struct Node{
    ll a11,a12,a21,a22;
    Node(){
        a11=1;
        a12=0;
        a21=0;
        a22=1;
    }
};
class segmnettree{
  public:
    vector<Node>tree;
    ll n;
    segmnettree(ll size){
        n=size;
        tree.resize(4*n);
    }
    Node combine(Node &a,Node &b,ll r){
        Node ans;
        ans.a11=((a.a11*b.a11)%r+(a.a12*b.a21)%r)%r;
        ans.a12=((a.a11*b.a12)%r+(a.a12*b.a22)%r)%r;
        ans.a21=((a.a21*b.a11)%r+(a.a22*b.a21)%r)%r;
        ans.a22=((a.a21*b.a12)%r+(a.a22*b.a22)%r)%r;
        return ans;

    }
    void build(ll idx,ll l,ll r,vector<Node>&arr,ll rem){

    if(l==r){
        tree[idx]=arr[l];
        return;
    }

    ll mid=(l+r)/2;

    build(2*idx,l,mid,arr,rem);
    build(2*idx+1,mid+1,r,arr,rem);

    tree[idx]=combine(tree[2*idx],tree[2*idx+1],rem);
}
    void update(ll idx,ll l,ll r,ll pos,ll a11,ll a12,ll a21,ll a22,ll rem){
        if(l==r){
            tree[idx].a11=a11;
            tree[idx].a12=a12;
            tree[idx].a21=a21;
            tree[idx].a22=a22;
            return;
        }
        ll mid=(l+r)/2;
        if(pos<=mid)  update(2*idx,l,mid,pos,a11,a12,a21,a22,rem);
        else          update(2*idx+1,mid+1,r,pos,a11,a12,a21,a22,rem);
        tree[idx]=    combine(tree[2*idx],tree[2*idx+1],rem);
    }
    Node query(ll idx,ll l,ll r,ll lq,ll rq,ll rem){
        if(r<lq || l>rq) return Node() ;
        if(l>=lq && r<=rq) return tree[idx];
        ll mid=(l+r)/2;
        Node left=query(2*idx,l,mid,lq,rq,rem);
        Node right=query(2*idx+1,mid+1,r,lq,rq,rem);
        return combine(left,right,rem);
    }
    void update(ll pos,ll a11,ll a12,ll a21,ll a22,ll r){
        update(1,0,n-1,pos,a11,a12,a21,a22,r);
    }
    Node query(ll lq,ll rq,ll r){
        return query(1,0,n-1,lq,rq,r);
    }
    void build(vector<Node>&arr,ll rem){
        build(1,0,n-1,arr,rem);
    }
};

int main()
{   
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll r,n,m;
    cin>>r>>n>>m;
    vector<Node>arr(n);
    segmnettree sg(n);
    for(ll i=0;i<n;i++){
            cin>>arr[i].a11>>arr[i].a12;
            cin>>arr[i].a21>>arr[i].a22;

    }
    sg.build(arr,r);
    for(ll i=0;i<m;i++){
        ll left,right;
        cin>>left>>right;
        left--,right--;
        Node ans=sg.query(left,right,r);
        cout<<ans.a11<<" "<<ans.a12<<endl;
        cout<<ans.a21<<" "<<ans.a22<<endl;
        cout<<endl;

    }

    return 0;
}