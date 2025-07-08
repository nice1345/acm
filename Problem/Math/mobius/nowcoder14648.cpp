#include<bits/stdc++.h>
using namespace std;
#define int long long
//题解：https://zhuanlan.zhihu.com/p/474258708
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<int>a(n+1),b(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    vector<bool>is(n+1,false);
    vector<int>mobius(n+1,0),primes;
    mobius[1]=1;is[1]=true;
    for(int i=2;i<=n;i++){
        if(!is[i]){primes.emplace_back(i);mobius[i]=-1;}
        for(int j:primes){
            if(j>n/i)break;
            is[i*j]=true;
            mobius[i*j]=-mobius[i];
            if(i%j==0){mobius[i*j]=0;break;}
        }
    }
    vector<int>cnt(n+1,0);
    int ans=0;
    for(int o=1;o<=n;o++){
        if(!mobius[o])continue;
        int cur=0;
        for(int i=o;i<=n;i+=o)cnt[a[b[i]]]++;
        for(int i=o;i<=n;i+=o)cur+=cnt[b[a[i]]];
        for(int i=o;i<=n;i+=o)cnt[a[b[i]]]=0;
        ans+=cur*mobius[o];
    }
    cout<<ans<<"\n";
    return 0;
}