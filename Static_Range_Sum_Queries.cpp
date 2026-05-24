#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Static Range Sum Queries
 * Source: CSES
 * Description: 
 * Range query: calculate the sum of elements in range [l, r].
 * Using prefix sums for efficiency.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll val;
        cin >> val;
        pref[i] = pref[i - 1] + val;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << "\n";
    }
    return 0;
}