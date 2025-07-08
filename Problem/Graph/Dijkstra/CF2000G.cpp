#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define vec vector
#define vi vec<int>
#define gg(nn) vec<basic_string<int>>g(nn+1,basic_string<int>());
#define pq priority_queue
#define cnm int n,m;cin>>n>>m;
inline void solve(){
    cnm
    int t0,t1,t2;cin>>t0>>t1>>t2;
    vec<basic_string<array<int,3>>>g(n+1,basic_string<array<int,3>>());
    for(int i=1;i<=m;i++){
        int u,v,l1,l2;cin>>u>>v>>l1>>l2;
        g[u]+={v,l1,l2};g[v]+={u,l1,l2};
    }
    vi dis(n+1,-1);
    pq<pii>q;
    dis[n]=t0;
    q.push({t0,n});
    while(!q.empty()){
        auto [time,cur]=q.top();
        q.pop();
        if(dis[cur]!=time)continue;
        //cout<<cur<<" "<<time<<"\n";
        dis[cur]=time;
        for(auto [to,l1,l2]:g[cur]){
            int to_dis;
            if(time<=t1||time-l1>=t2)to_dis=time-l1;
            else to_dis=max(time-l2,t1-l1);
            if(to_dis>dis[to])q.push({to_dis,to}),dis[to]=to_dis;
        }
    }
    cout<<dis[1]<<"\n";
}
/**
 反向倒推，得出最晚出发时间
 二分正推也是可以的
 事实证明，dijkstra算法用优先队列比带删除的set要快一些
 * */
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        cnm
        int t0,t1,t2;cin>>t0>>t1>>t2;
        vec<basic_string<array<int,3>>>g(n+1,basic_string<array<int,3>>());
        for(int i=1;i<=m;i++){
            int u,v,l1,l2;cin>>u>>v>>l1>>l2;
            g[u]+={v,l1,l2};g[v]+={u,l1,l2};
        }
        vec<int>dis(n+1,-1);
        set<pii>q;
        dis[n]=t0;
        q.insert({t0,n});
        while(!q.empty()){
            auto [time,cur]=*q.rbegin();
            q.erase({time,cur});
            for(auto [to,l1,l2]:g[cur]){
                int to_dis;
                if(time<=t1||time-l1>=t2)to_dis=time-l1;
                else to_dis=max(time-l2,t1-l1);
                if(to_dis>dis[to]){
                    if(dis[to]!=-1)q.erase({dis[to],to});
                    dis[to]=to_dis;
                    q.insert({to_dis,to});
                }
            }
        }
        cout<<dis[1]<<"\n";
    }
    return 0;
}
