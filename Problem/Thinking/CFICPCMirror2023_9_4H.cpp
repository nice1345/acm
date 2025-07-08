//https://codeforces.com/contest/1866/problem/H
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

ll qmi(ll a,ll b){
    ll res=(ll)1,p=a%mod;
    while (b){
        if(b&(ll)1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}
int n,k;
ll jie[200005],inv[200005];

int main() {
    scanf("%d%d",&n,&k);
    ll ans=1,sum=0;
    vector<ll>a(n+1);
    a[0]=1;
    for(int i=1;i<=n;i++){
        if(i>k)break;
        sum=(sum+(ll)(k-i+1))%mod;
        a[i]= (qmi((i+1),(k-i+1))*jie[i]%mod);
        ans=(ans+  (a[i]-a[i-1]+mod)%mod*jie[n]%mod*inv[n-i]%mod)%mod;
    }
//for(int i=1;i<=len;i++)printf("%lld ",tree[i]);
    printf("%lld",ans);

    return 0;
}
