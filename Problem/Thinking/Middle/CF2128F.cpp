#include <bits/stdc++.h>
//using namespace std;
//#define int long long
const int N = 1e6+5;
const long long mod = 998244353;
struct cmp{
    bool operator () (std::array<long long,3> o1,std::array<long long,3> o2){
        return o1[1]-o1[2]<o2[1]-o2[2];
    }
};
/**
 t1 通知时间
 t2 总时间

 假设存在一种规划，能找出一条路径(不经过k)，不难想到这条的边全部设置为l，其他设置为r

 找一找这条路径的性质
 那么这条路径任意两个点 u,v 满足 d(u,v)<=d(u,k)+d(v,k)
 可以证明这是一个充分必要条件

 只需要找出一条路径  满足  d(u,v)<=d(u,k)+d(v,k)
 转化题意，
 假设节点是城市， k是警察局，而你是某个劫匪。穿越 i/th边对劫匪来说需要 li秒，对市民和警察来说需要 ri秒。
 每当你穿越一座城市，这座城市的市民就会跑到警察局向警察发出警告。一旦警察收到警告，他们就会以最快的速度向四面八方派出警力追赶你。

 就是在找最短路径是，你还要知道这条路径警察局最晚通知的时间，从这个时间点到答你所在的点时间小于你从1点到达该点
 * **/
void solve() {
    int n,m,k;
    std::cin>>n>>m>>k;
    std::vector<std::vector<std::array<int,3>>>g(n+1);
    while(m--){
        int u,v,l,r;
        std::cin>>u>>v>>l>>r;
        g[u].push_back({v,l,r});
        g[v].push_back({u,l,r});
    }
    std::vector<long long>kt(n+1,LONG_LONG_MAX);
    std::priority_queue<std::array<long long,2>,std::vector<std::array<long long,2>>,std::greater<std::array<long long,2>>>q;
    q.push({0,k});
    while(!q.empty()){
        auto [ti,po] = q.top();
        q.pop();
        if(kt[po]!=LONG_LONG_MAX)continue;
        kt[po]=ti;
        for(auto [to,l,r]:g[po]){
            if(kt[to]!=LONG_LONG_MAX)continue;
            q.push({ti+r,to});
        }
    }
    std::vector<bool> vis(n+1,false);
    vis[k] = true;
    std::priority_queue<std::array<long long,3>,std::vector<std::array<long long,3>>,cmp>p;
    p.push({1,kt[1],0});
    while(!p.empty()){
        auto [cur,t1,t2] = p.top();
        p.pop();
        if(vis[cur])continue;
        vis[cur] = true;
        for(auto [to,l,r]:g[cur]){
            if(vis[to])continue;
            if(t2+l>=t1+kt[to])continue;
            p.push({to,std::min(t1,t2+l+kt[to]),t2+l});
        }
    }
    if(vis[n])std::cout<<"YES\n";
    else std::cout<<"NO\n";
}
void pw(){}
signed main() {
    int t;
    std::cin>>t;
    while(t--)solve();
    return 0;
}