#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod =1e9+7;
int qmi(int a,int b){
    int res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        b>>=1;
        p=p*p%mod;
    }
    return res;
}
//题解：https://zhuanlan.zhihu.com/p/474258708
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;cin>>n>>k;
    vector<bool>is(k+1,false);
    vector<int>mobius(k+1,0),primes;
    mobius[1]=1;is[1]=true;
    for(int i=2;i<=k;i++){
        if(!is[i]){primes.emplace_back(i);mobius[i]=-1;}
        for(int j:primes){
            if(j>k/i)break;
            is[i*j]=true;
            mobius[i*j]=-mobius[i];
            if(i%j==0){mobius[i*j]=0;break;}
        }
    }
    vector<int>g(k+1,-1);
    int ans=0;
    for(int i=1;i<=k;i++){
        int cur=0;
        for(int d=i;d<=k;d+=i){
            if(g[k/d]==-1)g[k/d]=qmi(k/d,n);
            cur+=mobius[d/i]*g[k/d]%mod,cur%=mod;
        }
        ans=(ans+cur*i%mod)%mod;
    }
    cout<<ans<<"\n";
    return 0;
}
/**
 int n,k;cin>>n>>k;
    vector<bool>is(k+1,false);
    vector<int>mobius(k+1,0),primes;
    mobius[1]=1;is[1]=true;
    for(int i=2;i<=k;i++){
        if(!is[i]){primes.emplace_back(i);mobius[i]=-1;}
        for(int j:primes){
            if(j>k/i)break;
            is[i*j]=true;
            mobius[i*j]=-mobius[i];
            if(i%j==0){mobius[i*j]=0;break;}
        }
    }
    vector<int>g(k+1,-1);
    int ans=0;
    for(int i=1;i<=k;i++){
        int cur=0;
        for(int d=i;d<=k;d+=i){
            if(g[k/d]==-1)g[k/d]=qmi(k/d,n);
            cur+=mobius[d/i]*g[k/d]%mod,cur%=mod;
        }
        ans=(ans+cur*i%mod)%mod;
    }
    cout<<ans<<"\n";
 * */