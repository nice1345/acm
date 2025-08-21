#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int N = 2e5 + 5;
const int mod = 998244353;
/**
 官解
 找出原始可爱的点，
 找出每个点的子树是否有以当前点为lca的相同颜色的点对，
 如果颜色有多个，当前点记权重，
 有一个，就更新为当前颜色，这样当前点不可爱，
 没有，在父节点或子树顺便取一种颜色，都不会增加可爱的点
 没有
 * **/
void solve() {
    int n,k;
    cin>>n>>k;
    vector<int>w(n),c(n);
    int flag = 0;
    for(int &i:w)cin>>i;
    for(int &i:c)cin>>i,flag=max(flag,i);
    vector<vector<int>>g(n);
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        --u;
        --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    if(flag == 0){
        cout<<0<<'\n';
        for(int i=0;i<n;++i)cout<<1<<' ';
        cout<<'\n';
        return;
    }
    vector<map<int,int>>h(n);
    vector<set<int>>d(n);
    vector<int> f(n);
    function<void(int,int)>dfs=[&](int cur,int last){
        f[cur] = last;
        int ms = -1, mz = -1;
        for(int to:g[cur]){
            if(last == to)continue;
            dfs(to,cur);
            //cout<<to<<' '<<h.size()<<'\n';
            if(mz < (int)h[to].size()){
                mz = h[to].size();
                ms = to;
            }
        }
        if(ms !=-1){
            swap(h[cur],h[ms]);
            for(int to:g[cur]){
                if(to == last || to == ms)continue;
                for( auto [key,val]:h[to]){
                    h[cur][key]+=val;
                }
            }
            for(int to:g[cur]){
                if(to == last || to == ms)continue;
                for( auto [key,val]:h[to]){
                    if(val<h[cur][key]){
                        d[cur].insert(key);
                    }
                }
            }
        }
        if(c[cur]!=0)++h[cur][c[cur]];
    };
    dfs(0,-1);
    long long cost = 0;
    for(int i=0;i<n;++i){
        if(((int)d[i].size()==1&&c[i]>0&&c[i]!=*d[i].begin())||(int)d[i].size()>1)cost+=(long long)w[i];
        if(c[i]==0&&!d[i].empty())c[i]=*d[i].begin();
    }
    for(int i=1;i<n;++i){
        int cur = f[i];
        while(cur != -1 && c[cur] == 0){
            c[cur] = c[i];
            cur = f[cur];
        }
    }
    function<void(int,int,int)>calc = [&](int cur,int last,int color){
        c[cur] = color;
        for(int to:g[cur]){
            if(to == last)continue;
            calc(to,cur,color);
        }
    };
    f[0]=-1;
    for(int i=0;i<n;++i){
        if(c[i]!=0){
            for(int so:g[i]){
                if(so == f[i])continue;
                if(c[so] == 0)
                    calc(so,i,c[i]);
            }
        }
    }
    cout<<cost<<'\n';
    for(int &i:c)cout<<i<<' ';
    cout<<'\n';
}
signed main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int _t = 1;
    std::cin >> _t;
    for(int _i = 1;_i<=_t;++_i){
        solve();
    }
    return 0;
}



