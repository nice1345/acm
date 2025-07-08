#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N =2005;
ll mod = (ll)1e9+(ll)7;
int n,m;
ll ans,tree[N],ans[2001],inv[2001];
ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while (b){
        if(b&1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}
int main() {
    ans[0]=1;
    for(int i=1;i<=2000;i++){
        ans[i]= ans[i - 1] * (ll)i % mod;
    }
    inv[2000]=qmi(ans[2000], (mod - (ll)2));
    //inv[0]=1;inv[1]=1;
    for(int i=1999;i>=0;i--)inv[i]=inv[i+1]*(ll)(i+1)%mod;

    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%lld",&tree[i]);

    for(int i=0;i<n;i++){
        ll res= ans[n] * inv[i] % mod * inv[n - i] % mod;             //强制任一i个同学没有特产，那么有c[len][i]种方法
                                 //隔板法，再通过可重复组合计算易得：
        for(int j=1;j<=m;j++)        //m个东西随意分给n-i个人方案数为c[m+len-i-1][len-i-1],一共的方案数就要把这些土特产的方案数全部乘起来
                                     //每一种物品分给n-i个人的方案数相乘就是全部物品分给n-i个人的方案数
            res= res * ans[tree[j] + n - i - 1] % mod * inv[n - i - 1] % mod * inv[tree[j]] % mod;

        if(i&1) ans=(ans-res+mod)%mod;      //求得f[i]后根据ans公式即可求解
        else ans=(ans+res+mod)%mod;
    }
    printf("%d\n",ans);
    return 0;
}
