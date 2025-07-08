//题解：https://blog.csdn.net/Euphria/article/details/132240658
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N=200005;
ll a[N];
ll n, m, k, c, d;

int check(ll x){
    vector<int> s(n + 1, 0);
    for(ll i = 1; i <= n; i ++){
        if(a[i] >= x)
            s[1] ++;
            //a[i]加上(等差序列最后一个)最大的值能够>=x,那(等差序列)必然存在一个值加上刚好>=x
        else if(a[i] + c + min(m - 1, i - 1) * d >= x){
            //max(1ll, i - m + 1)是选的长m的子序列第一个值的下标的最小值
            s[max(1ll, i - m + 1)] ++;
            ll cnt = 0;
            if(d != 0)
                cnt = (x - a[i] - c + d - 1) / d;
            //min(i, i - cnt)是选的长m的子序列第一个值的下标的最大值
            s[min(i, i - cnt) + 1] --;
            //长m的子序列第一个值的下标取[max(1ll, i - m + 1),min(i, i - cnt)]当前值(a[i])都能>=x
        }
    }
    for(int i = 1; i <= n - m + 1; i ++){
        s[i] += s[i - 1];
        //
        /**
         如果长m的子序列第一个值的下标取i,>=x的值就有s[i]个
         如果有一个是s[i]>=k
         说明第k大的值为x是有可能取到的，且有可能取到更大的值，也就是x有“可能”小了
         * */
        if(s[i] >= k)
            return 1;
    }
    ///一个都没有说明第k大的值不可能取到x，x"一定"大了
    return 0;
}


void solve(){
    cin >> n >> k >> m >> c >> d;
    for(int i = 1; i <= n; i ++)
        cin >> a[i];
    ll l = 0, r = 1e17;
    while(l < r){
        ll mid = l + r >> 1;
        //mid有可能小了
        if(check(mid))
            l = mid + 1;
            //mid一定大了
        else  r = mid;
    }
    cout << r - 1 << endl;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }

    return 0;
}


