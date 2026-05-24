#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Cirno and Number (Hard Version)
 * Description: 
 * Find a number composed of only digits from a given set that is closest to 'a'.
 * Uses binary search over generated numbers of relevant lengths.
 */

typedef long long ll;

ll pw(ll a, ll b) {
    ll res = 1;
    while (b--) res *= a;
    return res;
}

// Find k-th number of a certain length composed of given digits
ll get_num(ll index, const vector<ll>& digits, ll length) {
    ll k = digits.size();
    ll num = 0;
    for (ll pos = length - 1; pos >= 0; pos--) {
        ll block = 1;
        for (int i = 0; i < pos; i++) block *= k;
        ll digit_index = index / block;
        num = num * 10 + digits[digit_index];
        index %= block;
    }
    return num;
}

ll solve_len(ll a, const vector<ll>& digits, ll length) {
    if (length <= 0) return LLONG_MAX;
    if (length > 18) return LLONG_MAX; // Limit to 18 digits

    ll k = digits.size();
    ll total = 1;
    for (int i = 0; i < length; i++) {
        if (total > 2e18 / k) { total = 2e18; break; }
        total *= k;
    }

    ll lo = 0, hi = total - 1;
    while (hi - lo > 1) {
        ll mid = (lo + hi) / 2;
        ll val1 = get_num(mid, digits, length);
        ll val2 = get_num(mid + 1, digits, length);
        if (llabs(val1 - a) > llabs(val2 - a)) lo = mid;
        else hi = mid;
    }

    ll ans = llabs(get_num(lo, digits, length) - a);
    ans = min(ans, llabs(get_num(hi, digits, length) - a));
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll a, n;
        cin >> a >> n;
        vector<ll> digits(n);
        for (ll i = 0; i < n; i++) cin >> digits[i];
        sort(digits.begin(), digits.end());

        int length = to_string(a).length();
        ll ans = LLONG_MAX;
        
        // Check numbers with length-1, length, and length+1 digits
        ans = min(ans, solve_len(a, digits, length - 1));
        ans = min(ans, solve_len(a, digits, length));
        ans = min(ans, solve_len(a, digits, length + 1));

        cout << ans << "\n";
    }
    return 0;
}