#include<bits/stdc++.h>

using namespace std;
#define int long long
const int mod = 998244353;
const int N = 505;
int t, n, k, a[N], b[N], f[N], g, arr[N], brr[N], sum, cur, l, r, ans;

signed main() {
    std::cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; ++i)cin >> a[i];
        for (int i = 1; i <= n; ++i)cin >> b[i];
        for (int i = 0; i <= k; ++i)f[i] = 0;
        g = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i + 1] != -1 && b[i] != -1) {
                cur = a[i + 1] - b[i];
                if (cur >= 0) {
                    for (int j = 0; j < k; ++j) {
                        if (j + cur < k)f[j] = f[j + cur];
                        else f[j] = 0;
                    }
                } else {
                    sum = g;
                    g = 0;
                    for (int j = 0; j < k; ++j) {
                        sum += f[j];
                        f[j] = 0;
                    }
                    f[-cur] = sum % mod;
                }
            } else if (a[i + 1] == -1 && b[i] == -1) {
                arr[k] = brr[k] = 0;
                for (int j = k - 1; j >= 0; --j) {
                    arr[j] = (arr[j + 1] + f[j]) % mod;
                    brr[j] = (brr[j + 1] + f[j] * (k - j) % mod) % mod;
                }
                f[0] = brr[0];
                for (int j = 1; j < k; ++j)
                    f[j] = ((k - j) * (g + arr[0]) % mod + j * arr[j] + brr[j]) % mod;
                g = g * (k * (k + 1ll) / 2ll) % mod;
            } else {
                if (a[i + 1] != -1) {
                    l = a[i + 1] - k;
                    r = a[i + 1] - 1;
                } else {
                    l = 1 - b[i];
                    r = k - b[i];
                }
                brr[k] = 0;
                for (int j = k - 1; j >= 0; --j) {
                    brr[j] = (brr[j + 1] + f[j]) % mod;
                    f[j] = 0;
                }
                for (int j = l; j < 0; ++j)f[-j] = (g + brr[0]) % mod;
                if (r >= 0) {
                    for (int j = 0; j < k; ++j)f[j] = (f[j] + brr[j] - brr[min(j + r + 1, k)] + mod) % mod;
                    g = g * (r + 1ll) % mod;
                }
            }
        }
        ans = g;
        for (int i = 0; i < k; ++i)ans = (ans + f[i]) % mod;
        cout << 1ll * ans * (a[1] == -1 ? k : 1) * (b[n] == -1 ? k : 1) % mod << '\n';
    }
    return 0;
}