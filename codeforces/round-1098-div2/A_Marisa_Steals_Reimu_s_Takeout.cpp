#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Marisa Steals Reimu's Takeout
 * Description: 
 * Given n elements of values 0, 1, or 2.
 * Output count_0 + min(count_1, count_2) + abs(count_1 - count_2)/3.
 * Represents some regrouping logic.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n;
        cin >> n;
        ll count_0 = 0, count_1 = 0, count_2 = 0;
        for (ll i = 0; i < n; i++) {
            ll val;
            cin >> val;
            if (val == 0) count_0++;
            else if (val == 1) count_1++;
            else if (val == 2) count_2++;
        }
        if (count_2 >= count_1) {
            cout << count_0 + count_1 + (count_2 - count_1) / 3 << "\n";
        } else {
            cout << count_0 + count_2 + (count_1 - count_2) / 3 << "\n";
        }
    }
    return 0;
}