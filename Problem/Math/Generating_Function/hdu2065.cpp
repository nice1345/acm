
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 100;
int T;
ll n,ans;
ll qmi(ll a,ll b){
    ll res=1,p=a;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr); cout.tie(nullptr);
while(scanf("%d",&T)){
    if(T==0)break;
    for(int t=1;t<=T;t++){
        scanf("%lld",&n);
        ans= (qmi(2,(n-(ll)1))+qmi(4,(n-(ll)1)))%mod;
        cout<<"Case "<<t<<": "<<ans<<endl;
    }
    cout<<"\n";
}

    return 0;
}
