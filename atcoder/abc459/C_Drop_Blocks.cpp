#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

/**
 * Problem: Drop Blocks
 * Description: 
 * Uses Policy-Based Data Structure (Ordered Set) to handle ranking and frequency updates.
 */

typedef long long ll;
typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q;
    if (!(cin >> n >> q)) return 0;
    
    ordered_set s;
    vector<ll> freq(n, 0);
    for (int i = 0; i < n; i++) s.insert({0, i});

    ll rem = 0;
    while (q--) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            x--;
            s.erase({freq[x], x});
            freq[x]++;
            s.insert({freq[x], x});
            auto p = *s.find_by_order(0);
            if (p.first > rem) rem++;
        } else {
            ll x;
            cin >> x;
            cout << s.size() - s.order_of_key({x + rem, -1}) << "\n";
        }
    }
    return 0;
}