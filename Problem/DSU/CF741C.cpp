#include<bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<int>f(n*2+1,0),d(n*2+1,0);
    iota(f.begin()+1,f.end(),1);
    function<int(int)>find=[&](int x){
        if(x!=f[x]){
            int fa=f[x];
            f[x]=find(f[x]);
            d[x]=(d[x]+d[fa])%2;
        }
        return f[x];
    };
    for(int i=2;i<=n*2;i+=2){
        d[i]=1;f[i]=f[i-1];
    }
    vector<pair<int,int>>h(n);
    for(auto &[i,j]:h){
        cin>>i>>j;
        int fi=find(i),fj=find(j);
        if(fi!=fj){
            f[fj]=fi;
            d[fj]+=d[i]-d[j]+1;
        }
    }
    for(auto [i,j]:h){
        find(i);find(j);
        d[i]=(d[i]%2+2)%2;
        if(d[i]==0)d[i]=2;
        d[j]=(d[j]%2+2)%2;
        if(d[j]==0)d[j]=2;
        cout<<d[i]<<" "<<d[j]<<"\n";
    }
    return 0;
}