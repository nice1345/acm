#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int N = 5e5 + 5;
const int mod = 998244353;
/**
 所有点的度数之和为2n,
 最坏情况，随便找一条路径，长度小于n，到每个点时，都得等待这个点的度数时间，等待时间不会超过2n
 时间最长就是3n
 但是边的数量太多
 所以就枚举时间，在每个时间，每个点都只能走一条边，或者等待，就是O(1)
 时间复杂度，O(n^2)
 * **/
void solve() {
    int n, m;
    cin >> n >> m;
    int nnn = n*3;
    vector<vector<int>> g(n);
    int u, v;
    vector<int>d(n,0);
    while (m--) {
        cin >> u >> v;
        --u;
        --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        ++d[u];
        ++d[v];
    }
    int time = 0;
    vector<int>f(n,300000),dp(n,300000);
    f[0]=0;
    while(f[n-1]==300000){
        for(int i=0;i<n;++i)dp[g[i][time%d[i]]]=min(dp[g[i][time%d[i]]],f[i]);
        for(int i=0;i<n;++i){
            f[i]=min(f[i]+1,dp[i]);
            dp[i]=300000;
        }
        ++time;
    }
    cout<<time<<' '<<f[n-1]<<'\n';
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