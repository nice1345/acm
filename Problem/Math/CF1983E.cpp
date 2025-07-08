#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int mod =1e9+7;
ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
int ne,n,k,a,ans,c,odd;
/**
 一开始就脑残往排列组合想

 将非特殊球排列
 奇数位被第一个人拿去
 将非特殊球插入到空位中
 奇数空位的球被第一个人拿去
 剩下的就是概率计算
 * */
void solve() {
    a= ans=0;
cin>>n>>k;
for(int i=0;i<k;i++){cin>>ne;a+=ne;}
for(int i=0;i<n-k;i++){cin>>ne;ans+=ne;}
a%=mod;ans%=mod;
odd=(n-k+1ll)>>1;
c= odd * qmi(n-k,mod-2ll) % mod * ans % mod;
odd=(n-k+2ll)>>1;
c=(c+odd*qmi(n-k+1ll,mod-2ll)%mod*a%mod)%mod;
cout << c << " " << (a + ans - c + mod) % mod << "\n";
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
