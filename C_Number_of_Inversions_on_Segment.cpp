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
    vector<ll> v;
    ll inv=0;
    Node(){
        v.resize(41,0);
    }
};
class segmenttree{
   public:
    vector<Node>tree;
    ll n;
    segmenttree(ll size){
    n=size;
    tree.resize(4*n);
    }
    Node combine(Node &a,Node &b){

    Node ans;

    vector<ll> pref(41,0);

    pref[0]=b.v[0];

    for(ll i=1;i<=40;i++){
        pref[i]=pref[i-1]+b.v[i];
    }

    ll merge_inversion=0;

    for(ll i=0;i<=40;i++){

        if(a.v[i]){

            if(i>0)
                merge_inversion += a.v[i]*pref[i-1];
        }

        ans.v[i]=a.v[i]+b.v[i];
    }

    ans.inv=a.inv+b.inv+merge_inversion;

    return ans;
}
    void build(vector<ll>&arr,ll l,ll r,ll idx){
        if(l==r){
            tree[idx].v[arr[l]]=1;
            tree[idx].inv=0;
            return ;
        }
        ll mid=(l+r)/2;
        build(arr,l,mid,2*idx);
        build(arr,mid+1,r,2*idx+1);
        tree[idx]=combine(tree[2*idx],tree[2*idx+1]);
    }
    void update(ll l,ll r,ll pos,ll val,ll idx){
        if(pos<l || pos>r) return ;
        if(l==r){
            Node a=Node();
            a.v[val]=1;
            a.inv=0;
            tree[idx]=a;
            return ;
        }
        ll mid=(l+r)/2;
        if(pos<=mid) update(l,mid,pos,val,2*idx);
        else update(mid+1,r,pos,val,2*idx+1);
        tree[idx]=combine(tree[2*idx],tree[2*idx+1]);
    }
    Node query(ll idx,ll l,ll r,ll lq,ll rq){
        if(r<lq || l>rq) return Node();
        if(l>=lq && r<=rq) return tree[idx];
        ll mid=(l+r)/2;
        Node left_child=query(2*idx,l,mid,lq,rq);
        Node right_child=query(2*idx+1,mid+1,r,lq,rq);
        return combine(left_child,right_child);
    }
    void build(vector<ll>&arr){
        return build(arr,0,n-1,1);
    }
    void update(ll pos,ll val){
        return update(0,n-1,pos,val,1);
    }
    Node query(ll lq,ll rq){
        return query(1,0,n-1,lq,rq);
    }

};
int main()
{
    ll n,q;
    cin>>n>>q;
    vector<ll>arr;
    for(ll i=0;i<n;i++){
       ll va;
       cin>>va;
       arr.push_back(va);
    }
    segmenttree sg(n);
    sg.build(arr);
    while(q--){
        ll op;
        cin>>op;
        if(op==1){
           ll left,right;
           cin>>left>>right;
           left--,right--;
           cout<<sg.query(left,right).inv<<endl;
        }
        else{
            ll pos,val;
            cin>>pos>>val;
            pos--;
            sg.update(pos,val);
        }
    }
    return 0;
}