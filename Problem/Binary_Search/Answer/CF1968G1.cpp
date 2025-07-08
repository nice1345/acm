//题解：https://zhuanlan.zhihu.com/p/696549425
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
/**
 二分答案咋没看出来呢
 存在单调性，可以二分前缀长度len
 利用kmp或者哈希找出子串为s[0~len-1]的不相交的子串个数不简单的很
 * */
void solve() {
    int n, _, k;
    string s;
    cin >> n >> _ >> k >> s;
    vector<int> ne(n + 1, 0);
    ne[0] = -1;
    for (int i = 1, j = -1; i < n; i++) {
        while (j >= 0 && s[j + 1] != s[i])
            j = ne[j];
        if (s[j + 1] == s[i])
            j++;
        ne[i] = j;
    }
    auto check = [&](int m) -> bool {
        if (m == 0)
            return 1;
        string t = s.substr(0, m);
        int tmp = 0;
        for (int i = 0, j = -1; i < n; i++) {
            while (j != -1 && s[i] != t[j + 1])
                j = ne[j];
            if (s[i] == t[j + 1])
                j++;
            if (j == m - 1) {
                tmp++;
                j = -1;
            }
        }
        return tmp >= k;
    };
    int l = 0, r = n / k;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << l << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }

    return 0;
}
