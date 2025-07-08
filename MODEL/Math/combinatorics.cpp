
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
const ll mod = 1e9+7;
ll fac[N],inv[N];
ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
void init(){
    fac[0]=1;inv[0]=fac[1]=1;inv[1]=1;
    //法一(快速幂)
    for(int i=2;i<N;i++)fac[i]=(ll)i*fac[i-1]%mod;
    inv[N-1]=qmi(fac[N-1],mod-(ll)2);
    for(int i=N-2;i>1;i--)inv[i]=(ll)(i+1)*inv[i+1]%mod;

    //法二(不用快速幂)
//    for (int i=2;i<N;i++) {
//        inv[i]=(mod-mod/(ll)i)*inv[(int)(mod%i)]%mod;
//        inv[i]+=mod;inv[i]%=mod;
//    }
//    for(int i=2;i<N;i++){
//        fac[i]=(ll)i*fac[i-1]%mod;
//        inv[i]*=inv[i-1];
//        inv[i]%=mod;
//    }
}
ll A(int a,int b){return fac[a]*inv[a-b]%mod;}
ll C(int a,int b){return fac[a]*inv[a-b]%mod*inv[b]%mod;}

int main() {
    cin.tie(0)->sync_with_stdio(0);


    return 0;
}
