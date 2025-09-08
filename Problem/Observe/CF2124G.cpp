#include <bits/stdc++.h>
using namespace std;
#define ll long long
/**
 i j   ai+=aj   aj=0
 i一定是前缀min
 j一定是后缀max   如果不是 将j变成右边的后缀max一定更优
 假设al，ar 是  ai 左边右边的前缀min  将   ai  变成  al或者更大的值  a1到al的和不会改变
 所以讨论将ai变成ai到al的每个值   设ai 变为ai+x

 重点
 枚举每个前缀min ai复杂度就是al-ai  合起来就是 a1 - (前缀min最后一个)min(a2,a2...an)
 又因为a1不大于n    min(a2,a2...an)>=1  复杂度就是n

 这个x的位置肯定越靠右越好   直接枚举后缀max 知道后缀max>=al-ai
 然后计算ai 到ar的和 , 然后其余部分不会改变
 先处理 a(i+1) 到 ar 前缀min  前缀min和  二分就能算出来  或者用单调性枚举 可以干到O(n)
 * **/
int n;
const int maxN = 1e6 + 10;
int a[maxN];
ll best[maxN];
ll pref[maxN];
int sec_mn[maxN];
ll pref_sec[maxN];
int MN[maxN];
int f[maxN];
void pw (){}
signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int _t = 1;
    std::cin >> _t;
    for (int _i = 1; _i <= _t; ++_i) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 0; i <= n - 1; i++)best[i] = 0;
        vector<int> suf_max;
        suf_max.reserve(n);
        for (int i = n; i >= 1; i--)
            if (suf_max.empty() || a[i] > a[suf_max.back()])
                suf_max.emplace_back(i);
        int mn = 1e9;
        sec_mn[0] = 1e9;
        MN[0] = 1e9;
        int ind = -1;
        for (int i = 1; i <= n; i++) {
            sec_mn[i] = sec_mn[i - 1];
            if (a[i] < mn) {
                if (ind != -1) {
                    f[ind] = i;
                }
                sec_mn[i] = mn;
                mn = a[i];
                ind = i;
            }
            else if (a[i] < sec_mn[i]) {
                sec_mn[i] = a[i];
            }
            MN[i] = mn;
            pref[i] = pref[i - 1] + mn;
            pref_sec[i] = pref_sec[i - 1] + sec_mn[i];
        }
        f[ind] = n + 1;
        best[0] = pref[n];
        vector<int> st{n + 1};
        a[n + 1] = -1e9;
        for (int i = n; i >= 1; i--) {
            if (MN[i - 1] > a[i]) {
                for (int id: suf_max) {
                    if (id <= i) break;
                    int cur_mn = min(a[i] + a[id], MN[i - 1]);
                    int l = 0;
                    int r = st.size();
                    while (r - l > 1) {
                        int mid = (l + r) / 2;
                        if (a[st[mid]] <= cur_mn) l = mid;
                        else r = mid;
                    }
                    int upto = min(id - 1, st[l] - 1);
                    ll val = pref[i - 1] + cur_mn * 1LL * (upto - i + 1);
                    if (upto + 1 < id) {
                        int upup = min(f[i], id);
                        val += pref_sec[upup - 1] - pref_sec[upto];
                        val += pref[id - 1] - pref[upup - 1];
                    }
                    best[id - i] = max(best[id - i], val);
                    if (a[i] + a[id] >= MN[i - 1]) break;
                }
            }
            while (!st.empty() && a[i] <= a[st.back()]) st.pop_back();
            st.emplace_back(i);
        }
        for (int i = n - 2; i >= 0; i--) best[i] = max(best[i], best[i + 1]);
        for (int i = 0; i < n; i++) cout << best[i] << " ";
        cout << '\n';
    }
    return 0;
}





