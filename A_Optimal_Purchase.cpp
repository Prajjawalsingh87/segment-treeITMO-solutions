#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Optimal Purchase
 * Description: 
 * Simple math logic for optimal grouping/purchase.
 * Given n items, price a for 1 item, price b for 3 items.
 * Output the minimum cost to buy n items.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n, a, b;
        cin >> n >> a >> b;
        if (3 * a <= b) {
            cout << n * a << "\n";
        } else {
            // Either buy groups of 3 and the remainder individually, or buy one extra group of 3 if it's cheaper.
            cout << min((n / 3) * b + min((n % 3) * a, b), n * a) << "\n";
        }
    }
    return 0;
}