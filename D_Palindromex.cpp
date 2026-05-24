#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Palindromex
 * Description: 
 * Simple logic problem involving palindromic symmetry and MEX.
 * Finds the MEX of elements in a range that maintains palindromic structure.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(2 * n);
        int l_zero = -1, r_zero = -1;
        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
            if (a[i] == 0) {
                if (l_zero == -1) l_zero = i;
                r_zero = i;
            }
        }

        auto get_mex = [](set<ll>& s) {
            ll mex = 0;
            while (s.count(mex)) mex++;
            return mex;
        };

        ll res = 0;
        // Symmetric expansion from zero positions
        if (l_zero != -1) {
            set<ll> s;
            s.insert(0);
            int L = l_zero, R = r_zero;
            bool ok = true;
            while (L >= 0 && R < 2 * n) {
                if (a[L] == a[R]) {
                    s.insert(a[L]);
                    L--; R++;
                } else break;
            }
            res = max(res, get_mex(s));
            
            // Single point expansions
            set<ll> s1, s2;
            int c1 = 0;
            while (l_zero - c1 >= 0 && l_zero + c1 < 2 * n) {
                if (a[l_zero - c1] == a[l_zero + c1]) s1.insert(a[l_zero - c1]);
                else break;
                c1++;
            }
            res = max(res, get_mex(s1));

            int c2 = 0;
            while (r_zero - c2 >= 0 && r_zero + c2 < 2 * n) {
                if (a[r_zero - c2] == a[r_zero + c2]) s2.insert(a[r_zero - c2]);
                else break;
                c2++;
            }
            res = max(res, get_mex(s2));
        } else {
            res = 0; // Or handle no zeros
        }
        cout << res << "\n";
    }
    return 0;
}