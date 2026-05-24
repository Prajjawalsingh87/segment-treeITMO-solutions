#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Party Monster
 * Description: 
 * Simple logic check for balanced parentheses based strictly on counts.
 * Given a string of '(' and ')', output "YES" if the count of '(' equals the count of ')'.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n;
        cin >> n;
        string str;
        cin >> str;
        ll count_open = 0, count_close = 0;
        for (int i = 0; i < n; i++) {
           if (str[i] == ')') count_close++;
           else count_open++;
        }
        if (count_open == count_close) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}