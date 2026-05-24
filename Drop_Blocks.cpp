
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long

typedef tree<
    pair<ll,ll>,
    null_type,
    less<pair<ll,ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;

int main()
{
    ll n,q;
    cin>>n>>q;
    ordered_set s;
    ll rem=0;
    vector<ll> freq(n,0);
    for(ll i=0;i<n;i++){
        s.insert({0,i});
    }
    while (q--)
    {
        ll op;
        cin>>op;
        if(op==1){
             ll x;
             cin>>x;
             x--;
             s.erase({freq[x],x});

             freq[x]++;

            s.insert({freq[x],x});
            auto p=*s.find_by_order(0);

            if(p.first>rem){
                rem++;
            }
        }
        else{
            ll x;
            cin>>x;
           cout<<s.size() - s.order_of_key({x+rem, -1})<<endl;
        }
    }
    
    return 0;
}