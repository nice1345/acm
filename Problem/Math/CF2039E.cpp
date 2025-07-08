#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vec vector
#define i128 __int128
const int N=1e6;
const int mod=998244353;
int i2;
/*
 f[i]为长度i，逆序对>序列最大数
 ans=f[n]+num(逆序对！>序列最大数)
 num(逆序对！>序列最大数)一定是在变成f[i]之后一直加在末尾
 或者  {000} {010} {111}
 假设3<i<j
 由i转变到j  f[i]可以在末尾加(j-i-1)次导致逆序对不变，
 在小于逆序对的i个数前面加1次，使逆序对增加变成f[j]
 f[j]=f[i]*i  (3<i<j)
 f[j]也可以由逆序对为1转变而来
 {000} {010} {111}  加在任意0前面
 dp即可
 * */
int qmi(int a,int b){
    a%=mod;
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void solve() {
    int n;cin>>n;
    if(n==2)cout<<1<<"\n";
    else if(n==3)cout<<2<<"\n";
    else{
        vector<int>f(n+1,0);
        //由逆序对为1转变而来
        for(int i=4;i<=n;i++)f[i]+=(i*i%mod-3ll*i+mod)*i2%mod;
        int sum=0,ans=n-1ll;
        for(int i=4;i<=n;i++){
            //由逆序对>1转变而来
            f[i]=(f[i]+sum)%mod;
            //变成f[i]之后一直加在末尾
            ans=(ans+f[i])%mod;
            sum=(sum+f[i]*i%mod)%mod;
        }
        cout<<ans<<"\n";
    }
}

signed main() {
    i2= qmi(2ll,mod-2ll);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}