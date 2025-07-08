/**
不难发现，当第一-次有一个点被染成蓝色后，在之后的移动中，可以忽略染成红色，再染成蓝色这个过
我们称第一个被染成蓝色的点为r。那么不难发现，PA比Pp提前到达了这个节点，考虑后续Pp的
所有操作，PA可以在到达r后一个一个复原这些操作，那么后续PB走过的所有节点就已经被染成红
那么假设我们知道了r这将是一个经典问题，假设树上距离r最远的点和r的距离是d,那么答案就是
2(n- 1)- d。
 * */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

void solve() {
    int n;
    cin>>n;
    int a,b;
    cin>>a>>b;
    vector<vector<int>>que(n+1);
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        que[u].push_back(v);
        que[v].push_back(u);
    }
    vector<int>dep(n+1,0);
    vector<int>father(n+1);
    function<void(int,int)>dfs = [&](int u,int fa){
        father[u]=fa;
        for(auto x:que[u]){
            if(x == fa)continue;
            dep[x]=dep[u]+1;
            dfs(x,u);
        }
    };
    dep[a]=1;
    dfs(a,a);
    int ab=b;
    int ci=0;
    while(dep[ab]>(dep[a]+dep[b])/2){
        ab=father[ab];
        ci++;
    }
    dep[ab]=1;
    dfs(ab,ab);
    int ans=1e18;
    for(int i=1;i<=n;i++){
        ans=min(ans,2*(n-1)+ci-dep[i]+1);
    }
    cout<<ans<<endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }

    return 0;
}
