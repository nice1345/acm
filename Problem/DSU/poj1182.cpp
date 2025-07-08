#include<bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;cin>>n>>k;
    vector<int>f(n+1,0),d(n+1,0);
    iota(f.begin()+1,f.end(),1);
    function<int(int)>find=[&](int x){
        if(x!=f[x]){
            int fa=f[x];
            f[x]=find(f[x]);
            d[x]=(d[x]+d[fa])%3;
        }
        return f[x];
    };
    int ans=0;
    while(k--){
        int op,a,b;cin>>op>>a>>b;
        if(a>n||b>n){
            ans++;
            continue;
        }
        int fa=find(a),fb=find(b);
        if(op==1){
            if(fa==fb){
                if((d[a]-d[b])%3!=0)ans++;
            }
            else{
                d[fb]+=(d[a]-d[b])%3;
                f[fb]=fa;
            }
        }
        else{
            if(fa==fb){
                if(((d[b]-d[a])%3+3)%3!=1)ans++;
            }
            else{
                d[fb]+=(d[a]-d[b])%3+1;
                f[fb]=fa;
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}