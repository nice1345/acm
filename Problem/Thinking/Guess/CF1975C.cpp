/**
 实际上就是所有区间中位数最大值
 先筛长度为2的区间
 筛长度为3的区间，中位数处于中间的情况已经被第一种情况包含

 长度大于3
 假设中位数不在边缘
 设比中位数大的个数ma,比中位数小的个数mi
 区间里中位数位置右边的rma,rmi,左边的lma,lmi
 rma+lma>=rmi+lmi
 不可能出现rma<rmi&&lma<lmi
 定然是rma>=rmi||lma>=lmi
 那这个区间就可以将一个边界缩小至
 只找中位数在边缘的中位数的位置

 所以长度大于3只考虑边界为中位数的情况
 m为中位数 设a<m b>=m
 从中位数边界往另一个方向走 定然是2个小于m的数，不然会属于区间为3的情况
 m a a b a b a
 长度大于3且考虑边界为中位数，必然有两个大于m的数相连
 (看上式，从中位数边界往另一个方向走 定然是2个小于m的数，若没有两个大于m的数相连，m不可能为中位数)
 有两个大于m的数相连，属于第一种情况，且产生的答案一定比m大
 任何大于3的区间的答案都小于区间长度小于等于3的答案

 所以只看区间长度小于等于3的答案
 * */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, min(a[i], a[i + 1]));
    }
    for (int i = 0; i < n - 2; i++) {
        ans = max(ans, min(a[i], a[i + 2]));
    }
    cout << ans << '\n';
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
