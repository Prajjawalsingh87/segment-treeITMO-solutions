#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Digit String
 * Description: 
 * Given a string of digits. Count occurances of 4 and 8.
 * Perform some transformation on the remaining string (2 and 6 are 'even', others 'odd').
 * Find the minimum cost to make the string follow a specific prefix/suffix pattern.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        string str;
        cin >> str;
        ll cnt = 0;
        string new_str = "";
        for (ll i = 0; i < str.size(); i++) {
            if (str[i] - '0' == 4 || str[i] - '0' == 8) cnt++;
            else new_str += str[i];
        }
        
        if (new_str.empty()) {
            cout << cnt << "\n";
            continue;
        }

        vector<ll> prefix_odd_sum(new_str.size(), 0), suffix_odd_sum(new_str.size(), 0);
        ll count_odd = 0;
        for (int i = 0; i < new_str.size(); i++) {
            if (new_str[i] != '2' && new_str[i] != '6') count_odd++;
            prefix_odd_sum[i] = count_odd;
        }
        count_odd = 0;
        for (ll i = (ll)new_str.size() - 1; i >= 0; i--) {
            if (new_str[i] != '2' && new_str[i] != '6') count_odd++;
            suffix_odd_sum[i] = count_odd;
        }

        ll ans = 1e18;
        for (ll i = 0; i < new_str.size(); i++) {
            ll prefix_odd = prefix_odd_sum[i];
            ll suffix_eve = (ll)new_str.size() - i - 1 - suffix_odd_sum[i];
            ans = min(ans, prefix_odd + suffix_eve + cnt);
        }
        cout << ans << "\n";
    }
    return 0;
}