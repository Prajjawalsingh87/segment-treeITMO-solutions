#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll pw(ll a,ll b){
    ll res=1;

    while(b--){
        res*=a;
    }

    return res;
}

ll get_num(ll index, vector<ll>&vt, ll length){

    ll k = vt.size();

    ll num = 0;

    for(ll pos = length-1 ; pos >= 0 ; pos--){

        ll block = pw(k,pos);

        ll digit_index = index / block;

        num = num * 10 + vt[digit_index];

        index %= block;
    }

    return num;
}

ll solve_len(ll a, vector<ll>&vt, ll length){

    if(length<=0) return LLONG_MAX;

    ll total = pw(vt.size(), length);

    ll lo = 0;
    ll hi = total - 1;

    while(hi - lo > 1){

        ll mid = (lo + hi) / 2;

        ll val1 = get_num(mid,vt,length);
        ll val2 = get_num(mid+1,vt,length);

        if(abs(val1-a) > abs(val2-a)){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }

    ll ans = LLONG_MAX;

    ans = min(ans, llabs(get_num(lo,vt,length)-a));
    ans = min(ans, llabs(get_num(hi,vt,length)-a));

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while (t--)
    {
        ll a,n;
        cin >> a >> n;

        vector<ll> vt(n);

        for(ll i=0;i<n;i++)
            cin >> vt[i];

        sort(vt.begin(),vt.end());

        ll length = to_string(a).length();

        ll ans = LLONG_MAX;

        ans = min(ans, solve_len(a,vt,length-1));
        ans = min(ans, solve_len(a,vt,length));
        ans = min(ans, solve_len(a,vt,length+1));

        cout << ans << '\n';
    }

    return 0;
}