#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Adjacent Distinct String
 * Description: 
 * Given a string, rearrange its characters so that no two adjacent characters are the same.
 */

typedef long long ll;

void solve() {
    string s;
    if (!(cin >> s)) return;
    int n = s.size();
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    priority_queue<pair<int, char>> pq;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > (n + 1) / 2) {
            cout << "No\n";
            return;
        }
        if (freq[i] > 0) pq.push({freq[i], (char)('a' + i)});
    }

    cout << "Yes\n";
    string ans = "";
    pair<int, char> prev = {-1, '#'};
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        ans += curr.second;
        if (prev.first > 0) pq.push(prev);
        curr.first--;
        prev = curr;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) solve();
    return 0;
}