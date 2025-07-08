#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5E2 + 10, mod = 998244353;
int n, m;
int dp[N][N],f[N][N];
//卡特兰数的思路待写
signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;
    f[0][0] = 1;
    //f[i][j]表示1~i个数里面第一个人比另第二个人多拿j个数，且没多拿的数形成括号匹配
    for (int i = 1; i <= m; i ++)
        for (int j = 0; j <= m; j ++) {
            //至于括号匹配，括号匹配正反的方案数是一样的，所以可以这样dp,求反即是正，求正亦是反
            //1~i-1个数里面第一个人比另第二个人多拿j-1个数,第一个人再拿一个i，就多拿了j个数
            if (j) f[i][j] += f[i - 1][j - 1];
            //1~i-1个数里面第一个人比另第二个人多拿j+1个数,第二个人再拿一个i，就多拿了j个数
            if (j < m) f[i][j] += f[i - 1][j + 1];
            f[i][j] %= mod;
        }
    for (int i = 0; i <= m; i += 2) dp[1][i] = f[m][i];
    for (int i = 2; i <= n; i ++)
        for (int j = 0; j <= m; j ++)
            for (int k = 0; k <= j; k += 2)
                dp[i][j - k] += dp[i - 1][j] * f[m][k] % mod, dp[i][j - k] %= mod;

    cout << dp[n][0] << "\n";

    return 0;
}