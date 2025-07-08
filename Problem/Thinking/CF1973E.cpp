/**
 这题是真的抽象啊，题解也是抽象的很啊，看到一半心态崩了
 对于可能的区间[l,r]
 if l==r
 所有的 pi!=i pi+i都相同

 if l==r
 假设l<r
设mi为不在位置上的最小数,ma为不在位置上的最大数
 mi<=i<=ma
 条件1：l<=mi+n//不然mi只能与大于n的值交换，这不可能
 条件2：r>=ma+1//不然ma只能与小于1的值交换，这不可能
 条件3：又l<r  r>=max(l+1,ma+1)
 mi+1 ma+1 mi+n ma+n
       r    l
 结合条件123  [l,r]一定包含[ma+1,mi+n]的1个数m使得 每个i mi<=i<=ma都有位置可换
 这样确保每个i mi<=i<=ma都有位置可换

 m=c+i

 对于保每个i [l,r]存在c l<=c+i<=r,l<r c与i可以交换
 将m取到max[ma+1,mi+n]&&[l,r]([l,r]一定包含[ma+1,mi+n]的1个数m,所以不为空) 又l<r
 l<=c+i-1<=r,l<r c与i-1可以交换
如果l==min+n [ma+1,mi+n]&&[l,r]==mi+n
 将m取到min[ma+1,mi+n]&&[l,r]==min+n([l,r]一定包含[ma+1,mi+n]的1个数m,所以不为空) 又l<r
i mi  ma
c n   mi+n-ma
 l<=c+i+1<=r,l<r c与i+1可以交换

 i与i+1可换或者i与i-1，mi到ma可排序

 * */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

void solve(){
    int n;
    cin >> n;
    vector<int> p(n + 1);
    int mi = 1e9, ma = 0;       // 不在位置上的最小数和最大数
    for (int i = 1; i <= n; i++){
        cin >> p[i];
        if (p[i] != i)
            mi = min(mi, p[i]), ma = max(ma, p[i]);
    }
    if (ma < mi){
        cout << 1ll * (n * 2) * (n * 2 + 1) / 2 << endl;
        return;
    }
    ll ans = 0;
    int flag = 1;       // 是否可以使用一个l==r的区间让数组变成升序
    for (int i = 1; i <= n; i++)
        if (p[i] != i && i + p[i] != ma + mi)
            flag = 0;
    ans += flag;
    for (int l = 1; l <= mi + n; l++){      // l代表左边界
        if (l < ma + 1) ans += n * 2 - ma;      // ma + 1 为能取的最小右边界
        else ans += n * 2 - l;      // l + 1 为能取到的最小右边界
    }
    cout << ans << endl;
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
