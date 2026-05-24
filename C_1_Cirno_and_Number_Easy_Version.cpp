#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> vt;

void solve(ll cur, int len)
{
    if (len == 0)
        return;

    ll x = cur * 10 + 1;
    vt.push_back(x);
    solve(x, len - 1);

    ll y = cur * 10 + 2;
    vt.push_back(y);
    solve(y, len - 1);
}

ll check(ll num, ll a, ll d1, ll d2)
{
    ll val = 0;

    string str = to_string(num);

    for (char c : str)
    {
        if (c == '1')
            val = val * 10 + d1;
        else
            val = val * 10 + d2;
    }

    return llabs(val - a);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve(0, 18);

    sort(vt.begin(), vt.end());

    int t;
    cin >> t;

    while (t--)
    {
        ll a;
        int n;

        cin >> a >> n;

        ll d1, d2;
        cin >> d1 >> d2;

        if (d1 > d2)
            swap(d1, d2);

        ll lo = 0;
        ll hi = vt.size() - 1;

        while (hi - lo > 1)
        {
            ll mid = (lo + hi) / 2;

            ll val1 = check(vt[mid], a, d1, d2);
            ll val2 = check(vt[mid + 1], a, d1, d2);

            if (val2 < val1)
                lo = mid;
            else
                hi = mid;
        }

        cout << min(
            check(vt[lo], a, d1, d2),
            check(vt[hi], a, d1, d2)
        ) << '\n';
    }

    return 0;
}