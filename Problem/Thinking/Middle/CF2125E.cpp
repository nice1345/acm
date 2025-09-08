//
// Created by yanghao10 on 2025/9/8.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5,S=651,MOD=998244353;
int n,m;
ll f[2][N],g[S];
/**
 题解：https://www.luogu.com.cn/article/y3jfz99x
 * **/
void solve(){
    cin>>n>>m;
    if((ll)n*(n+1)/2>m+1){
        cout<<"0\n";
        return ;
    }
    if(n==1){
        cout<<m<<'\n';
        return ;
    }
    for(int i=0;i<=1;i++)
        for(int j=0;j<=m+1;j++){
            f[i][j]=0;
        }
    for(int j=0;j<=n;j++) g[j]=0;
    f[1][n]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m+1;j++){
            f[i&1][j]=g[j%(n-i+1)];
            (g[j%(n-i+1)]+=f[(i&1)^1][j])%=MOD;
        }
        for(int j=0;j<=n;j++) g[j]=0;
    }
    ll ans=0;
    for(int i=1;i<=m+1;i++){
        ans+=f[n&1][i]*(m+1-i+1)%MOD;
        ans%=MOD;
    }
    cout<<ans<<'\n';
}
/**
 官解 不同点
 dp出n个两两不同的数
 f[i][j]代表  有1 i个两两不同的数  和为j
 dp[i][j]代表  没有1 i个两两不同的数  和为j
 可以 所有数+1(操作多次)  或者没有1+1
 f[i][j]=dp[i-1][j-1]  +1
 dp[i][j]=dp[i][j-i]+f[i][j-k*i]  j-k*i>0
 对%i 同余的下标前缀和优化
 * **/
signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int _t = 1;
    std::cin >> _t;
    for (int _i = 1; _i <= _t; ++_i) {
        solve();
    }
    return 0;
}