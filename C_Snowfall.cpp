#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Snowfall
 * Description: 
 * Given an array of integers. Regroup elements based on their divisibility by 6, 2, and 3.
 * Divisible by 6: placed alternately at the beginning and end.
 * Divisible by 2 (but not 6): placed after the 6s from the beginning.
 * Divisible by 3 (but not 6): placed before the 6s from the end.
 * Others: placed in the remaining middle.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> div6, div2, div3, others;
        for (ll i = 0; i < n; i++) {
            ll c;
            cin >> c;
            if (c % 6 == 0) div6.push_back(c);
            else if (c % 2 == 0) div2.push_back(c);
            else if (c % 3 == 0) div3.push_back(c);
            else others.push_back(c);
        }

        vector<ll> ans(n);
        int head = 0, tail = n - 1;
        
        // Place divisible by 6
        for (int i = 0; i < div6.size(); i++) {
            if (i % 2 == 0) ans[head++] = div6[i];
            else ans[tail--] = div6[i];
        }
        
        // Place divisible by 2
        for (ll val : div2) ans[head++] = val;
        
        // Place divisible by 3
        for (ll val : div3) ans[tail--] = val;
        
        // Place others
        for (ll val : others) ans[head++] = val;

        for (int i = 0; i < n; i++) {
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}