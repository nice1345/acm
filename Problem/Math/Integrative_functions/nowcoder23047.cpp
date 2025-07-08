#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int N=2e7+5,mod=1e9+7;
ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
int cnt=0;
vector<int>primes;
bool sg[N];
int val[N];
int ans=1;
void get_primes(int x){
    sg[1]=true;
    for(int i=2;i<=x;i++){
        if(!sg[i]){
            primes.emplace_back(i);cnt++;val[i]=qmi(i,x);
        }
        ans^=val[i];
        for(int j=0;j<cnt&&primes[j]<=x/i;j++){
            sg[primes[j] * i]=true;
            val[primes[j]*i]=val[i]*val[primes[j]]%mod;
            if(i%primes[j]==0)break;
        }
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    get_primes(n);
    cout<<ans<<"\n";
    return 0;
}