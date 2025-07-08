/**
 官解跟图解写的都一样：
 喵的，这写法感觉还有点像扫描线
 b是当前的峰值，出现了b,之前那些小于b/2的点不能作为左边界
 将b放入时只有出现新的大于2*b的峰值，才会将b删除，否则，未来出新的b，当前这个点就可以作为左边界
 图：https://www.cnblogs.com/extractstars/p/18223651
 * */
#include <bits/stdc++.h>
using namespace std;
#define vec vector
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
string s;
void solve1() {
    cin >> s;
    map<int, int> cnt;
    int b = 0;
    cnt[b]++;
    ll ans = 0;
    for (auto& c : s) {
        b += (c == '(' ? +1 : -1);
        //只要之前等于b的点过后没有出现>2*b的点都会作为左边界
        ans += cnt[b];
        //记录当前点
        ++cnt[b];
        while (cnt.begin()->first * 2 < b)
        //出现了b，之前小于b/2的点将不作数，不然b作为峰值减下去必定减到负值
            cnt.erase(cnt.begin());
    }
    cout << ans << '\n';
}
//高度是一点一点变化
//设峰值是y，每变化一次，就 high[(sum[i] - 1) / 2] = 0;，0到y/2都会变为0
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    int sum=0;
    vec<int> high(n + 1);
    high[0] = 1;
    ll ans = 0;
    for (int i = 0; i < n; i++){
        sum+=+(s[i] == '(' ? 1 : -1);
        ans += high[sum];
        high[sum]++;
        if (sum > 0)
            high[(sum - 1) / 2] = 0;
    }
    cout << ans <<"\n";
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    while (_--) {
        solve();
    }

    return 0;
}
