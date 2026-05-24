#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Koshary
 * Description: 
 * Simple logic problem based on parity.
 * Given two numbers a and b, output "NO" if both are odd, else "YES".
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        if (a % 2 == 1 && b % 2 == 1) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}