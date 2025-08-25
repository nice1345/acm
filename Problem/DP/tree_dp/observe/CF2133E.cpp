#include <bits/stdc++.h>
const int N = 105;
const long long mod = 998244353;
/**
 进行2操作全部弄成链
 树形dp
 在树上面将节点分为4种
 1:边界节点  没有子节点(排除删除节点)
 0:传递边界节点 子节点只有一个0或1节点(排除删除节点)
 2:中间节点  只有两个0或1节点(排除删除节点)
 3:删除节点  有2节点或三个以上0或1节点(排除删除节点)
 每个删除节点至少与4个节点绑定
 * **/
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    std::vector<int> col(n + 1, 0);//1:边界节点 2:中间节点 3:删除节点 0:传递边界节点
    std::vector<int> h;
    std::function<void(int, int)> dfs = [&](int cur, int fa) {
        int a1 = 0, a2 = 0;
        for (int to: g[cur])
            if (to != fa) {
                dfs(to, cur);
                if (col[to] == 1 || col[to] == 0)++a1;
                else if (col[to] == 2)++a2;
            }
        if (a2 > 0 || a1 > 2)col[cur] = 3, h.emplace_back(cur);
        else if (a1 == 2)col[cur] = 2;
        else if (a1 == 1)col[cur] = 0;
        else col[cur] = 1;
    };
    dfs(1, 0);
    std::cout << n + (int) h.size() << '\n';
    for (int i: h)std::cout << 2 << ' ' << i << '\n';
    for (int i: h)std::cout << 1 << ' ' << i << '\n';
    std::vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (vis[i] || col[i] != 1)continue;
        int cur = i, fa = 0;
        bool flag;
        while (true) {
            vis[cur] = true;
            std::cout << 1 << ' ' << cur << '\n';
            flag = true;
            for (int to: g[cur])
                if (col[to] != 3 && fa != to) {
                    flag = false;
                    fa = cur;
                    cur = to;
                    break;
                }
            if (flag)break;
        }
    }
}
signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int _t = 1;
    std::cin >> _t;
    for (int _i = 1; _i <= _t; ++_i) {
        solve();
    }
    return 0;
}






