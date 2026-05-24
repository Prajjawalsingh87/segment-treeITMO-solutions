#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Cirno and Number (Easy Version)
 * Description: 
 * Find a number composed of only digits d1 and d2 (d1 < d2) that is closest to 'a'.
 * The easy version allows searching through all possible numbers up to 18 digits.
 */

typedef long long ll;

vector<ll> candidates;

void generate(ll cur, int len, ll d1, ll d2) {
    if (len > 18) return;
    if (cur > 0) candidates.push_back(cur);
    
    if (cur > 2e18 / 10) return; // Avoid overflow
    
    generate(cur * 10 + d1, len + 1, d1, d2);
    generate(cur * 10 + d2, len + 1, d1, d2);
}

// Special case for generating numbers when d1=0 (cannot start with 0)
void generate_with_zero(ll cur, int len, ll d2) {
    if (len > 18) return;
    if (cur > 0) candidates.push_back(cur);
    if (cur > 2e18 / 10) return;

    generate_with_zero(cur * 10 + 0, len + 1, d2);
    generate_with_zero(cur * 10 + d2, len + 1, d2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll a;
    int n_ignored;
    ll d1, d2;
    if (!(cin >> a >> n_ignored >> d1 >> d2)) return 0;
    
    if (d1 > d2) swap(d1, d2);
    
    if (d1 == 0) {
        generate_with_zero(d2, 1, d2);
    } else {
        generate(0, 0, d1, d2);
    }
    
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    
    ll min_diff = LLONG_MAX;
    for (ll val : candidates) {
        min_diff = min(min_diff, llabs(val - a));
    }
    
    cout << min_diff << "\n";
    
    return 0;
}