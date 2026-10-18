#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Palindromex
 * Description:
 * Array of length 2n; find the maximum MEX over all palindromic subarrays.
 * Any palindrome with MEX > 0 must contain a 0, so we only expand around the
 * positions of the zeros.
 */

typedef long long ll;

// MEX of a set of non-negative integers.
ll get_mex(const set<ll>& s) {
    ll mex = 0;
    while (s.count(mex)) mex++;
    return mex;
}

// Check whether a[l..r] is a palindrome, collecting its values into st.
bool is_palindrome(const vector<ll>& a, int l, int r, set<ll>& st) {
    while (l >= 0 && l <= r) {
        st.insert(a[l]);
        st.insert(a[r]);
        if (a[l] != a[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        int m = 2 * n;
        vector<ll> a(m);
        int l_zero = -1, r_zero = -1;
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            if (a[i] == 0) {
                if (l_zero == -1) l_zero = i;
                r_zero = i;
            }
        }

        ll res = 1;  // a single 0 is always a palindrome with MEX 1
        int L = l_zero, R = r_zero;

        // Case 1: the segment between both zeros is a palindrome -> expand outwards.
        set<ll> s;
        s.insert(0);
        if (is_palindrome(a, L, R, s)) {
            while (L >= 0 && R < m && a[L] == a[R]) {
                s.insert(a[L]);
                L--; R++;
            }
            res = max(res, get_mex(s));
        }

        // Case 2: odd palindromes centred on the first zero / the last zero.
        // (L and R are deliberately the values left over from case 1, as in the
        //  original accepted solution.)
        set<ll> s1, s2;
        for (int c = 0; L - c >= 0 && L + c < m && a[L - c] == a[L + c]; c++) s1.insert(a[L - c]);
        for (int c = 0; R - c >= 0 && R + c < m && a[R - c] == a[R + c]; c++) s2.insert(a[R - c]);
        res = max(res, get_mex(s1));
        res = max(res, get_mex(s2));

        cout << res << "\n";
    }
    return 0;
}
