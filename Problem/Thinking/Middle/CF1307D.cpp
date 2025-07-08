#include<bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m,k;cin>>n>>m>>k;
    vector<bool>is(n+1,0);
    for(int i=0;i<k;i++){
        int ne;cin>>ne;
        is[ne]=1;
    }
    vector<vector<int>>g(n+1,vector<int>());
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    map<int,int>x,y;
    queue<pair<int,int>>q;
    vector<int>vis(n+1,0);
    q.push({1,0});
    vis[1]=1;
    int mi=0;
    while(!q.empty()){
        int cur=q.front().first,dis=q.front().second;
        if(cur==n)mi=dis;
        q.pop();
        if(is[cur])x[cur]=dis;
        for(int to:g[cur]){
            if(vis[to])continue;
            vis[to]=1;
            q.push({to,dis+1});
        }
    }
    for(auto &i:vis)i=0;
    q.push({n,0});
    vis[n]=1;
    while(!q.empty()){
        int cur=q.front().first,dis=q.front().second;
        q.pop();
        if(is[cur])y[cur]=dis;
        for(int to:g[cur]){
            if(vis[to])continue;
            vis[to]=1;
            q.push({to,dis+1});
        }
    }
    vector<pair<int,int>>h;
    for(int i=1;i<=n;i++)
        if(is[i]){
            h.push_back({x[i]-y[i],i});
            //cout<<i<<" "<<x[i]<<" "<<y[i]<<"\n";
        }
    sort(h.rbegin(),h.rend());
    int ma=y[h[0].second];
    int ans=0;
    for(int i=1;i<h.size();i++){
        ans=max(ans,ma+x[h[i].second]);
        ma=max(ma,y[h[i].second]);
    }
    ans++;
    ans=min(ans,mi);
    cout<<ans<<"\n";
    return 0;
}