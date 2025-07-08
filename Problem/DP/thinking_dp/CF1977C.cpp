#include <bits/stdc++.h>
/**
  现特判答案为n的情况，数组中的最大值不是数组中每个数的倍数

  答案不为为n的情况，数组中的最大值是数组中每个数的倍数
  (没想到的点)任意子序列的lcm一定为数组中的最大值的因子
  枚举lcm为数组中的最大值的每个因子，子序列最大长度
 */
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;


void solve() {
    int n, ma = 0, mm = 0;
    cin >> n;
    vector<int> a(n);
    for (int &i: a) {
        cin >> i;
        ma = max(ma, i);
    }
    for (int i: a)
        if (ma % i)mm++;

    if (mm) {
        std::cout << n << "\n";
        return;
    }
    sort(a.begin(), a.end());
    int ans = 0;
    auto check = [&](int d) {
        if (*lower_bound(a.begin(), a.end(), d) == d)
            return;
        int lcm = 1;
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (d % a[i] == 0) {
                lcm = std::lcm(lcm, a[i]);
                cnt++;
            }

        if (lcm == d)
            ans = max(ans, cnt);

    };

    for (int d = 1; d * d <= ma; d++) {
        if (ma % d == 0) {
            check(d);
            check(ma / d);
        }
    }
    std::cout << ans << "\n";
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }


    int n;
    cin >> n;
    vector<int> v(n);
    map<int, bool> tem;
    for(auto &x:v){
        cin >> x;
        tem[x]=true;
    }

    sort(v.begin(), v.end());

    int resp=0;

    for(int i=n-1; i>=0; i--){
        int lcm=1, cr=0;
        for(int j=i; j>=0; j--){
            int pos=lcm/__gcd(lcm, v[j])*v[j];
            if(pos!=v[i] && tem[pos])continue;
            lcm=pos;
            if(lcm>v.back()){
                cr=n;
                break;
            }
            cr++;
        }
        if(lcm!=v[i])resp=max(resp, cr);
    }

    cout << resp << '\n';

    return 0;
}
