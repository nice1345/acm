#include<bits/stdc++.h>
using namespace std;

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m,e;cin>>n>>m>>e;
    vector<vector<int>>g(n+1);
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        g[u].emplace_back(v);
    }
    vector<bool>vis(m+1,false);
    vector<int>link(m+1,0);
    int ans=0;
    function<bool(int)>dfs=[&](int cur){
        for(int to:g[cur]){
            if(vis[to])continue;
            vis[to]=true;
            if(!link[to]||dfs(link[to])){
                link[to]=cur;
                return true;
            }
        }
        return false;
    };
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++)vis[j]=false;
        if(dfs(i))ans++;
    }
    cout<<ans;
    return 0;
}