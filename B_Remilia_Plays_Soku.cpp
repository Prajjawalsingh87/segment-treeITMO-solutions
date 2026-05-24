#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        ll n, x1, x2, k;
        cin >> n >> x1 >> x2 >> k;

        if (n <= 3)
        {
            cout << 1 << '\n';
            continue;
        }

        ll d = abs(x1 - x2);

        d = min(d, n - d);

        cout << d + k << '\n';
    }

    return 0;
}