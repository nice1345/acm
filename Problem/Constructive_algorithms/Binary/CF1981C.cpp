/**
 哇趣，赛时完全没想到这和静态开点很像
 还得是别人的线性写法
 * */
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define vec vector
#define pii array<int,2>
const int N = 1000005;
ll mod = (ll)998244353;
int a[200009], ans[200009];
void solve() {
    int n, j = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != -1)
            ans[i] = a[i], j = 1;
        else
            ans[i] = ans[i - 1] / 2;
        if (j && ans[i] == 0)
            ans[i] = 2;
    }


    ans[n + 1] = ans[0];
    for (int i = n; i >= 1; i--) {
        if (a[i] == -1)
            ans[i] = max(ans[i], ans[i + 1] / 2);
        if (ans[i] == 0)
            ans[i] = 2;
    }
    for (int i = 1; i < n; i++) {
        if (ans[i] != ans[i + 1] / 2 && ans[i] / 2 != ans[i + 1]) {
            cout << "-1" << "\n";
            return;
        }
    }
    cout << ans[1];
    for (int i = 2; i <= n; i++) {
        cout << " " << ans[i];
    }
    cout << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _= 1;
    cin >> _;
    while (_--) {
        solve();
    }

    return 0;
}
