#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int N = 2e5 + 5;
const int mod = 998244353;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n, vector<int>()),
            fr(n,vector<int>(k,-1)),
            vis(n, vector<int>(k, 2));
    vector<int>f(n,-1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f[0] = 0;
    vis[0][0] = 2;
    queue<array<int, 4>> q;
    q.push({0, 0, 0, 0});
    while (!q.empty()) {
        auto [cur, fa, b, d] = q.front();\
        q.pop();
        ++d;
        b = (b + 1) % k;
        for (int to: g[cur]) {
            if (vis[to][b] == 0 || (b != 1 && to == fa) || (vis[to][b] == 1 && cur == fr[to][b]))continue;
            --vis[to][b];
            if (vis[to][b] == 1) {
                fr[to][b]=cur;
                if(b == 0){
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
