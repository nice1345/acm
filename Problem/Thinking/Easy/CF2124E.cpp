#include <bits/stdc++.h>
const int N = 2e5 + 5;
const int mod = 998244353;
/**
 题解思路
 以下情况无解
 最大值大于剩下值之和
 所有值之和为奇数

 先思考n=3
 a b c
 只有一次的方案很好判断，这里讨论只有两次的
 假设 b > a > c
 a 和 b 之间两边之差绝对值最小
 b c 减去 a后一定能分成两个相等的部分
 证明
 (b+c-a)/2 <= c
 b+c-a <= 2*c
 b<=a+c

 n>3 分成上述连续的三个部分  则答案操作次数一定小于3
 先分成两部分 a b(a>b)
 再把a分成两个部分，每个部分都大于(a-b)/2就行
 * **/
void solve() {
    int n;
    long long sum = 0, lc = 0;
    std::cin >> n;
    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i)std::cin >> a[i], sum += a[i], lc = std::max(lc, a[i]);
    if ((sum & 1) == 1 || lc > sum - lc) {
        std::cout << "-1\n";
        return;
    }
    std::vector<std::vector<long long>> ans;
    std::vector<long long> b(n + 1);
    std::function<void(int, int, long long)> calc = [&](int st, int en, long long val) {
        std::fill(b.begin(), b.end(), 0);
        long long vv = val >> 1;
        for (int i = st; i <= en; ++i) {
            if (a[i] < vv) {
                vv -= a[i];
                b[i] = a[i];
            } else {
                b[i] = vv;
                break;
            }
        }
        vv = val >> 1;
        for (int i = en; i >= st; --i) {
            if (a[i] < vv) {
                vv -= a[i];
                b[i] = a[i];
            } else {
                b[i] = vv;
                break;
            }
        }
        std::swap(a, b);
        for (int i = 1; i <= n; ++i) {
            b[i] = b[i] - a[i];
        }
        ans.push_back(b);
    };
    while (true) {
        sum = 0;
        long long cnt = 0;
        lc = LONG_LONG_MAX;
        int idx = 1;
        for (int i = 1; i <= n; ++i)sum += a[i];
        for (int i = 1; i < n; i++) {
            cnt += a[i];
            if (std::abs(sum - cnt - cnt) < lc) {
                lc = sum - cnt - cnt;
                idx = i;
            }
        }
        if (lc == 0) {
            ans.push_back(a);
            break;
        } else if (lc > 0)calc(idx + 1, n, lc);
        else calc(1, idx, -lc);
    }
    std::cout << ans.size() << '\n';
    for (auto v: ans) {
        for (int i = 1; i <= n; ++i)std::cout << v[i] << ' ';
        std::cout << '\n';
    }
}
signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int _ = 1;
    std::cin >> _;
    for (int _i = 1; _i <= _; ++_i) {
        solve();
    }
    return 0;
}




