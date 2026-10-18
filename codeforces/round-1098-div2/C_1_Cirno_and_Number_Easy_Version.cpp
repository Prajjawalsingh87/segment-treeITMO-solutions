#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Cirno and Number (Easy Version)
 * Description:
 * For each test case, find the minimum |x - a| over all numbers x whose decimal
 * digits are only d1 or d2.
 * Approach: pre-generate every "pattern" of 1..18 digits made of 1s and 2s
 * (1 -> d1, 2 -> d2, with d1 <= d2). In sorted order the mapped values are
 * increasing, so |value - a| is unimodal and can be binary searched.
 */

typedef long long ll;

vector<ll> patterns;

void generate(ll cur, int len) {
    if (len == 0) return;
    ll x = cur * 10 + 1;
    patterns.push_back(x);
    generate(x, len - 1);
    ll y = cur * 10 + 2;
    patterns.push_back(y);
    generate(y, len - 1);
}

// Map a pattern of 1s/2s to the real number using digits d1/d2, return |value - a|.
ll dist(ll pattern, ll a, ll d1, ll d2) {
    ll val = 0;
    for (char c : to_string(pattern)) val = val * 10 + (c == '1' ? d1 : d2);
    return llabs(val - a);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    generate(0, 18);
    sort(patterns.begin(), patterns.end());

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll a, d1, d2;
        int n;
        cin >> a >> n >> d1 >> d2;
        if (d1 > d2) swap(d1, d2);

        ll lo = 0, hi = (ll)patterns.size() - 1;
        while (hi - lo > 1) {
            ll mid = (lo + hi) / 2;
            if (dist(patterns[mid + 1], a, d1, d2) < dist(patterns[mid], a, d1, d2)) lo = mid;
            else hi = mid;
        }
        cout << min(dist(patterns[lo], a, d1, d2), dist(patterns[hi], a, d1, d2)) << "\n";
    }
    return 0;
}
