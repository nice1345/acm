#include <bits/stdc++.h>
const long long mod = 998244353;
template<class T,class F,const F P>
struct modint{
    using M = modint<T,F,P>;
    T v;
    modint(F x = 0){v=x%P;}
    constexpr M operator+(const M &o)const{F u=v;u+=o.v;mo(u);M res;res.v=u;return res;}
    constexpr M operator-(const M &o)const{F u=v;u-=o.v;mo(u);M res;res.v=u;return res;}
    constexpr M operator*(const M &o)const{return M((F)v*o.v);}
    constexpr M operator/(const M &o)const{return M((F)v*o.inv().v);}
    constexpr M& operator++(){++v;if constexpr(v==P)v=0;return *this;}
    constexpr M& operator--(){--v;if constexpr(v==-P)v=0;return *this;}
    constexpr M& operator+=(const M &o){F u=v;u+=o.v;mo(u);v=u;return *this;}
    constexpr M& operator-=(const M &o){F u=v;u-=o.v;mo(u);v=u;return *this;}
    constexpr M& operator*=(const M &o){v=(F)v*o.v%P;return *this;}
    constexpr M& operator/=(const M &o){v=(F)v*o.inv().v%P;return *this;}
    constexpr M pow(F b){M res=1,a=*this;while(b){if constexpr(b&1)res*=a;a*=a;b>>=1;}return res;}
    constexpr M inv(){return pow(P-2);}
    constexpr void mo(F &u){if (u<-P)u+=P;if (u>P)u-=P;}
    friend std::ostream& operator<<(std::ostream& os, const M& o) {os << (o.v+P)%P;return os;}
};
using Mint = modint<int,long long,mod>;
/**
     题解：https://www.luogu.com.cn/article/s7g7ijar
     一位一位的进行dp
     p[i] 表示当前位为i且这个i属于以1开始的循环
     d[i][j]表示当前位为i+j且这个i+j属于以j+1开始的循环的前半段
     f[i][j]表示当前位为i,这个循环是以j+1开始的，且前半段已经结束，
     dp[j]表示 i:1~n,d[i][j]的和

     f[k][k] + p[1~n] -> p[1]
     f[k][k] + p[1~n] - p[j] -> d[j]
     dp[k] -> f[1][k]
     k:1~n
     可以发现转移的时候只是数组平移了一下，这里做个映射优化就可以省略掉一维的复杂度，只更新首项的值就行
     复杂度 n^2+n*m 局限于m不能太大
     * **/
void solve1() {
    int n, m;
    std::cin >> n >> m;
    if (n == 1) {
        if (m == 0)std::cout << 1 << '\n';
        else std::cout << 0 << '\n';
        while (m--)std::cin >> n >> n;
        return;
    }
    std::vector<long long> p(n + 1, 0),//以1开始的循环当前位置上的值,下标1开始
                           dp(n, 0);//循环前半部分总和
    std::vector<std::vector<long long>> f(n, std::vector<long long>(n, 0)),//循环后半部分终点的值,下标0开始
                                        d(n, std::vector<long long>(n, 0));//循环前半部分,下标0开始
    std::vector<std::vector<int>> h(n + 1, std::vector<int>());
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        h[u].emplace_back(v);
    }
    f[0][1] = 1;
    long long np = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = n; j > 0; --j)p[j] = p[j - 1];
        p[1] = np;
        for (int j = 1; j < n; j++) {
            p[1] = (p[1] + f[(j * i - i) % j][j]) % mod;
            f[(j * i - i) % j][j] = dp[j];
        }
        for (int j = 1; j < n; ++j) {
            d[i - 1][j] = (p[1] - p[j + 1] + mod) % mod;
            dp[j] = (dp[j] + p[1] - p[j + 1] + mod) % mod;
        }
        for (int k: h[i]) {
            if (k == 1) {
                p[1] = 0;
                for (int j = 1; j < n; ++j)f[(j * i - i) % j][j] = 0;
            } else {
                for (int j = std::max(1, k - i); j < k; ++j) {
                    dp[j] = (dp[j] - d[i + j - k][j] + mod) % mod;
                    d[i + j - k][j] = 0;
                }
                for (int j = k; j < n; ++j)f[(j * i - i + k - 1) % j][j] = 0;
                np = (np - p[k] + mod) % mod;
                p[k] = 0;
            }
        }
        np = (np + p[1]) % mod;
    }
    for (int i = 1; i < n; ++i)np = (np + f[(i * n - n + i - 1) % i][i]) % mod;
    np = (np % mod + mod) % mod;
    std::cout << np << '\n';
}

/**
 题解做法，复杂度 n^2+m,m可以为n^2
 **/

using namespace std;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<vector<bool>> banned(N, vector<bool>(N));
    for (int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        banned[x - 1][y - 1] = true;
    }
    vector<Mint> tot(N + 1);
    tot[N] = 1;
    vector<vector<Mint>> dp(N + 1, vector<Mint>(N + 1));
    vector<vector<int>> chain(N + 1, vector<int>(N + 1));

    for (int i = N - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) {
            chain[i][j] = 1 + chain[i + 1][j + 1];
            if (banned[i][j]) chain[i][j] = 0;
        }
    }

    vector<vector<Mint>> ssum(N + 2, vector<Mint>(N + 1));

    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j <= N - i; ++j) {
            if (j == 0) {
                for (int len = 1; len <= N - i; ++len) {
                    bool ok = chain[i][0] >= len;
                    if (!ok) break;
                    dp[i][j] += tot[i + len];
                    dp[i][j] -= dp[i + len][j + len];
                }
            } else {
                if (chain[i][j]) {
                    dp[i][j] += ssum[i + 1][j];
                    if (i + 1 + chain[i][j] <= N) {
                        dp[i][j] -= ssum[i + 1 + chain[i][j]][j];
                    }
                }
            }
            tot[i] += dp[i][j];
        }

        for (int j = 1; j < N; ++j) {
            ssum[i][j] = ssum[i + 1][j];
            if (chain[i][0] >= j) {
                ssum[i][j] += tot[i + j];
            }
        }
    }
    // cout << dp << endl;
    // cout << ssum << endl;
    cout << tot[0].v << '\n';
}


int main() {
    int _;
    std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
