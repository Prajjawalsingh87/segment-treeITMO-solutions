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
#include <bits/stdc++.h>
using namespace std;

#define ll long long

pair<ll, set<ll>> check(vector<ll>& a, ll left, ll right, set<ll> &st) {
    while (left>=0 and right>=0 and left<a.size() and right<a.size() and left <= right) {
        st.insert(a[left]);
        st.insert(a[right]);

        if (a[left] == a[right]) {
            left++;
            right--;
        } else {
            return {0, st};
        }
    }
    return {1, st};
}

int main() {
    ll t;
    cin >> t;
    // cout<<"Heelo";
    while (t--) {
        ll n;
        cin >> n;
        // cout<<"Heelo";
        vector<ll> a;
        ll left_zero=-1,right_zero=-1;
        ll zero_contain=0;
        for (ll i = 0; i < 2*n; i++) {
            ll c;
            cin >> c;
            a.push_back(c);
            if(c==0){
               if(left_zero ==-1) left_zero=i,right_zero=i;
               else right_zero=i;
            }
            
        }
        // cout<<"Heelo"<<endl;
        // cout<<"Heelo";
        ll ans = 1;
        set<ll> st;
        st.insert(0);

        ll left = left_zero, right = right_zero;
        // cout<<left<<" "<<right<<endl;
        auto result = check(a, left, right, st);
        ll b = result.first;
        ll correct_ans=0;
        st = result.second;
       

        if (b) {
            
            while (left >= 0 && right <= 2*n - 1) {
                if (a[left] == a[right]) {
                    st.insert(a[left]);
                    left--;
                    right++;
                } else {
                    break;
                }
            }
            
            ll ans = 0;
            for (auto &it : st) {
                if (ans == it) ans++;
            }

            correct_ans=max(correct_ans,ans);
        } else {
            correct_ans=max(correct_ans,ans);
        }
        set<ll>new_set1,new_set2;
        ll cnt=0;
        while(left-cnt>=0 && left+cnt<=2*n-1){
            if(a[left-cnt]==a[left+cnt]){
                new_set1.insert(a[left-cnt]);
            }
            else{
                break;
            }
            cnt++;
        }
        cnt=0;
        while (right-cnt>=0 && right+cnt<2*n-1)
        {
            if(a[right-cnt]==a[right+cnt]){
                new_set2.insert(a[right-cnt]);
            }
            else{
                break;
            }
            cnt++;
        }
        ans=0;
        for(auto it:new_set1){
            if(ans==it) ans++;
        }
        correct_ans=max(correct_ans,ans);
        ans=0;
        for(auto it:new_set2){
            if(ans==it) ans++;
        }
        correct_ans=max(correct_ans,ans);
        cout<<correct_ans<<endl;
        
    }

    return 0;
}