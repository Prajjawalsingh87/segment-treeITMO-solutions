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
int main()
{
    ll t;
    cin>>t;
  while (t--)
{
    string str;
    cin >> str;
    ll cnt=0;
    string new_str="";
    int last_index_2=-1,last_index_6=-1;
    for(ll i=0;i<str.size();i++){
        if(str[i]-'0'==4 || str[i]-'0'==8) {
             cnt++;
        }
        else {
            new_str+=str[i];
        }
    }
    vector<ll>prefix_odd_sum(new_str.size(),0),suffix_odd_sum(new_str.size(),0);
    ll count_even=0,count_odd=0;
    for(int i=0;i<new_str.size();i++){
        if(new_str[i]=='2' || new_str[i]=='6') count_even++;
        else count_odd++;
        prefix_odd_sum[i]=count_odd;
    }
    count_odd=0;
    for(ll i=new_str.size()-1;i>=0;i--){
        if(new_str[i]!='2' && new_str[i]!= '6'){
            count_odd++;
        }
        suffix_odd_sum[i]=count_odd;
    }

    ll ans=1e18;
    for(ll i=0;i<new_str.size();i++){
            ll prefix_odd=prefix_odd_sum[i];
            ll suffix_eve=new_str.size()-i-1-suffix_odd_sum[i];
            ans=min(ans,prefix_odd+suffix_eve+cnt);
    }
    if(ans==1e18) cout<<cnt<<endl;
    else cout<<ans<<endl;
    
}
    
    return 0;
}