//题解：https://www.cnblogs.com/Lanly/p/18277192
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define vec vector
#define pii array<int,2>
const int N = 1000005;
ll mod = (ll) 998244353;
ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
void solve() {
int n,k;cin>>n>>k;
int invn=qmi(n,mod-2ll);//  1/n
int invn1=qmi(n-1ll,mod-2ll);//  1/n-1
//移动 2*(1/n)*(1/n-1)
int move = 2ll * invn * (n - 1) % mod * invn % mod;
//不移动
int stay = (1ll - move + mod) % mod;
//移动到特定位置
int move1 = 2ll * invn * invn % mod;
//移动到特定位置以外的位置
int move2 = (1ll - move1 + mod) % mod;
//dp[0]呆在1的概率，dp[1]呆在非1的概率
static int dp[2],dp1[2];
dp[0]=1;
for(int i=1;i<=k;i++){
    //不动或者从非一球移动到一球
    dp1[0]=(dp[0]*stay%mod+dp[1]*move1%mod)%mod;
    //从一球移动或者从非一球移动到非一球
    dp1[1]=(dp[0]*move%mod+dp[1]*move2%mod)%mod;
    dp[0]=dp1[0];
    dp[1]=dp1[1];
}
//容易发现第2,3,..n个球没有本质区别，其概率都是一样的，他们的和为dp[1],每一位分别为dp[1]/n-1
int ans=(dp[0] + 1ll * (n + 2) * (n - 1) / 2 % mod * dp[1] % mod * invn1 % mod) %mod;

cout<<ans;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    //cin >> T;
    while (_--) {
        solve();
    }

    return 0;
}
