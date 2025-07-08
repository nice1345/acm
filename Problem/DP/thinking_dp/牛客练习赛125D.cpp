//题目链接：https://ac.nowcoder.com/acm/contest/82612/D
/**
 用max树状数组去优化dp[i][j]=max(dp[i-1][j]+c[i][j],dp[i][j-1]+c[i][j])
 * */
#include "bits/stdc++.h"
using namespace std;
using i64 = int64_t;
template <class T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int n = 0) : n(n), a(n, T()) {}
    void modify(int i, T x) {
        for (i++; i <= n; i += i & -i) {
            a[i - 1] += x;
        }
    }
    T get(int i) {
        T res = T();
        for (; i > 0; i -= i & -i) {
            res += a[i - 1];
        }
        return res;
    }
};
struct Max {
    i64 x;
    Max(i64 x = 0) : x(x) {}
    Max &operator+=(const Max &a) {
        x = max(a.x, x);
        return *this;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n, vector<int>(m));
    vector<int> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            v.push_back(a[i][j]);
        }
    }

    //对颜色离散化
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int nv = v.size();
    vector<vector<tuple<int, int, int>>> pos(nv);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int c;
            cin >> c;
            int k = lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
            pos[k].emplace_back(i, j, c);
        }
    }

    i64 ans = 0;
    for (int i = 0; i < nv; i++) {
        vector<int> y;
        for (auto [_, yi, c] : pos[i])
            y.emplace_back(yi);

        sort(y.begin(), y.end());
        y.erase(unique(y.begin(), y.end()), y.end());

        int ny = y.size();
        Fenwick<Max> f(ny);
        for (auto [_, yi, c] : pos[i]) {
            yi = lower_bound(y.begin(), y.end(), yi) - y.begin();
            i64 res = f.get(yi + 1).x + c;
            ans = max(ans, res);
            f.modify(yi, res);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}