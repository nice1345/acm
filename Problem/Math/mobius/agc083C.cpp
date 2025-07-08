#include<bits/stdc++.h>

#define int long long
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

void solve();

signed main() {
    fast
    int t = 1;
//    cin >> t;
    while (t--) solve();
}

const int N = 300005;
int n, m, p[N], sta[N];
set<int> nei[N];
vector<pair<int, int>> ans;
vector<int> neii[N];

void solve() {
    int head(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        neii[u].push_back(v);
        neii[v].push_back(u);
        nei[u].insert(v);
        nei[v].insert(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        while (head > 0 && nei[sta[head]].empty()) {
            head--;
        }
        if (head > 0 && (nei[sta[head]].count(p[i]) == 0)) {
            ans.push_back({p[i], sta[head]});
        }
        for (auto x: neii[p[i]])nei[x].erase(p[i]);
        sta[++head] = p[i];
    }
    cout << ans.size() << '\n';
    for (auto x: ans)cout << x.first << " " << x.second << '\n';
    return;
}
/*
8 1
 1 2
 2 1 4 5 6 7 8 3
 */
