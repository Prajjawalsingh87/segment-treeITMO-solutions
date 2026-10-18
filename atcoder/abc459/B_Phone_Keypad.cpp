#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Phone Keypad
 * Description: 
 * Translates letters to their corresponding digits on a standard phone keypad.
 * a-c -> 2, d-f -> 3, g-i -> 4, j-l -> 5, m-o -> 6, p-s -> 7, t-v -> 8, w-z -> 9.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    
    vector<int> mp(26);
    for (char c : "abc") if(c) mp[c - 'a'] = 2;
    for (char c : "def") if(c) mp[c - 'a'] = 3;
    for (char c : "ghi") if(c) mp[c - 'a'] = 4;
    for (char c : "jkl") if(c) mp[c - 'a'] = 5;
    for (char c : "mno") if(c) mp[c - 'a'] = 6;
    for (char c : "pqrs") if(c) mp[c - 'a'] = 7;
    for (char c : "tuv") if(c) mp[c - 'a'] = 8;
    for (char c : "wxyz") if(c) mp[c - 'a'] = 9;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ans = ans * 10 + mp[s[0] - 'a'];
    }
    cout << ans << "\n";
    return 0;
}