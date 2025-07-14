#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int N = 2e5 + 5;
const int mod = 998244353;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int,int>>> g(n, vector<pair<int,int>>());
    vector<vector<int>>vis(n,vector<int>(k,2));
    vector<vector<bool>>fr(n*2 - 2,vector<bool>(k,false));
    vector<int>f(n,-1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].emplace_back(v,i*2);
        g[v].emplace_back(u,i*2|1);
    }
    f[0] = 0;
    queue<array<int, 4>> q;
    q.push({0, 0, 0, 0});
    while (!q.empty()) {
        auto [cur, fa, b, d] = q.front();\
        q.pop();
        ++d;
        b = (b + 1) % k;
        for (auto [to,e]: g[cur]) {
            if (vis[to][b] == 0 || (b != 1 && to == fa) || fr[e][b])continue;
            --vis[to][b];
            if (!fr[e][b]) {
                fr[e][b]=true;
                if(b == 0 && f[to] == -1){
                    f[to] = d/k;
                }
            }
            q.push({to, cur, b, d});
        }
    }
    for (int i = 1; i < n; ++i)cout << f[i] << ' ';
    cout << '\n';
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
