#include<bits/stdc++.h>
using namespace std;
//题解：https://zhuanlan.zhihu.com/p/565553750
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<int>g(n+1,0);
    int ans=0;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u]++;g[v]++;
        if(g[u]==2)ans++;
        if(g[v]==2)ans++;
    }
    cout<<n-ans<<"\n";
    return 0;
}