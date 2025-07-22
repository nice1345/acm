//
// Created by yanghao10 on 2025/7/9.
//
#include <bits/stdc++.h>
#define int long long
/**
从后往前倒着dp
dp[i][j]表示i~n有j个位置被用掉了
枚举当前位置i删和不删的情况
不删
dp[i][j] += dp[i+1][j+1]
删
根据dp[i+1][j]求dp[i][j+1]
i 可以在 i~n这些位置选一个作为右端点删除
假设选位置k,k >= i,作为区间右端点
这些位置有j个被用掉，还剩(n-i+1-j)个
要删除i,左端点必须<=i,在1~i里面选，有i个
所以
f[i][j+1] = f[i+1][j] * i * (n-i+1-j)
**/
void solve() {
    int n, m, ans = 0;
    std::cin >> n >> m;
    std::vector<int> f(n + 1);
    f[0] = 1;
    for (int i = n; i > 0; --i) {
        for (int j = n - i + 1; j > 0; --j) {
            f[j] = (f[j] + f[j - 1] * i % m * (n - i - j + 2ll) % m) % m;
        }
    }
    for (int i:f) {
        //std::cout<<ans<<' '<<i<<'\n';
        ans = (ans+i)%m;
    }
    std::cout<<ans<<'\n';
}

signed main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
