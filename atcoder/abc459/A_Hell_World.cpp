#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Hell World
 * Description: 
 * Dummy problem logic to print HelloWorld while skipping one character.
 */

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    if (!(cin >> n)) return 0;
    string s = "HelloWorld";
    for (int i = 0; i < 10; i++) {
        if (i + 1 == n) continue;
        cout << s[i];
    }
    cout << "\n";
    return 0;
}