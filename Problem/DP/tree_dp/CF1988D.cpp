#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vec vector
#define gg(n)  vec<basic_string<int>>g(n+1,basic_string<int>());
const int N = 3e5+5;
/*
 转化题意的好题，但这个树形dp我都写不出来
 脑袋秀逗了，树形dp一般是从下往上考虑
 设dp[i][k]为i这颗子树里i节点在第k轮删去的最小值
 dp[i][k]=i*a[i]+min(dp[son[i]][!k])
 * */
int n,u,v;
int a[N];
void solve() {
    cin >> n;
    gg(n);
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++){cin>>u>>v;g[u]+=v;g[v]+=u;}
    vec<vec<int>>dp(n+1,vec<int>(25)),l(n+1,vec<int>(25)),r(n+1,vec<int>(25));
    function<void(int,int)>dfs=[&](int no,int fa){
        for(int so:g[no]){
            if(so==fa)continue;
            dfs(so,no);
            for(int i=1;i<20;i++)
                dp[no][i]+=min(l[so][i-1],r[so][i+1]);
        }
        int mi=LONG_LONG_MAX;
        l[no][0]=r[no][20]=mi;
        for(int i=1;i<20;i++){
            dp[no][i]+=i*a[no];
            l[no][i]=mi=min(mi,dp[no][i]);
        }
        mi=LONG_LONG_MAX;
        for(int i=19;i>1;i--)
            r[no][i]=mi=min(mi,dp[no][i]);
    };
    dfs(1,0);
    cout<<l[1][19]<<"\n";
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

