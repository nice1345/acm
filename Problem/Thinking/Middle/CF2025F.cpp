#include<bits/stdc++.h>
using namespace std;
//dfs遍历，一条链先从末尾进行操作，回溯时判断当前的操作
//此题有重边，若要保证每条边遍历一次，遍历时应将那条边标记删除
void solve(){
    int n,m;cin>>n>>m;
    vector<vector<array<int,4>>>g(n+1);
    vector<int> d(n+1,0),h(n+1,0);
    vector<pair<int,int>>s(m);
    vector<bool> vis(m,false);
    vector<string> pw(m,"");
    for(int i=0;i<m;++i){
        int u,v;cin>>u>>v;
        s[i]={u,v};
        g[u].push_back({v,u,v,i});
        g[v].push_back({u,u,v,i});
        ++d[v];++d[u];
    }
    function<bool(int)>dfs=[&](int cur){
        while(!g[cur].empty()){
            //for(auto [to,x,y,id]:g[cur]){
            auto [to,x,y,id]=g[cur].back();
            //删除
            g[cur].pop_back();
            if(vis[id])continue;
            --d[x];--d[y];
            //标记
            vis[id]=true;
            if(dfs(to)){
                if(h[cur]>0){
                    --h[cur];
                    if(cur==x)pw[id]="x";
                    else pw[id]="y";
                }
                else{
                    ++h[cur];
                    if(cur==x)pw[id]="x";
                    else pw[id]="y";
                }
            }
            else{
                if(h[to]>0){
                    --h[to];
                    if(to==x)pw[id]="x";
                    else pw[id]="y";
                }
                else{
                    ++h[to];
                    if(to==x)pw[id]="x";
                    else pw[id]="y";
                }
            }
        }
        return h[cur]==0;
    };
    for(int i=1;i<=n;++i)
        if(d[i])
            dfs(i);
    for(int i=0;i<=n;i++)h[i]=0;
    for(int i=0;i<m;++i){
        if(pw[i]=="x"){
            if(h[s[i].first]==0){
                ++h[s[i].first];
                cout<<"x+\n";
            }
            else{
                --h[s[i].first];
                cout<<"x-\n";
            }
        }
        else{
            if(h[s[i].second]==0){
                ++h[s[i].second];
                cout<<"y+\n";
            }
            else{
                --h[s[i].second];
                cout<<"y-\n";
            }
        }
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    //cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}