//快速：https://www.luogu.com.cn/record/150794290
//快速：https://www.luogu.com.cn/record/149913999
#include <bits/stdc++.h>
#define vec vector
#define pii pair<int,int>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
void solve() {
int n,u,v,w;
cin>>n;
//vec<pii>g[len+1];
//vector<vector<pair<int,int>>>g(len+1,vector<pair<int,int>>());
vec<vec<pii>>g(n+1);
for(int i=0;i<n-1;i++){
    cin>>u>>v>>w;
    g[u].push_back({v,w});
    g[v].push_back({u,w});
}

//构建dfs序
int cnt=0;
vec<int>dfn(n+1);
function<void(int,int)>get_dfn=[&](int no,int fa){
    dfn[no]=cnt++;
    for(pii so:g[no]){
        if(so.first==fa)continue;
        get_dfn(so.first,no);
    }
};
get_dfn(1,0);
//lca
//st[i][j]表示i节点往根节点方向走2^j步所达到的点
int bs=__lg(n);
vec<vec<int>>st(n+1,vec<int>(bs+1));

//dis[i][j] i走2^j步中权值最小的一步
vec<vec<int>>dis(n+1,vec<int>(bs+1));

//深度deep
//父节点f
vec<int>deep(n+1,0);
    function<void(int,int)>get_deep=[&](int no,int fa){
        deep[no]=deep[fa]+1;
        for(pii so:g[no]){
            if(so.first==fa)continue;
            get_deep(so.first,no);
            st[so.first][0]=no;
            dis[so.first][0]=so.second;
        }
    };
get_deep(1,1);
//处理st表
st[1]=vec(bs+1,1);
for(int l=1;l<=bs;l++)
    for(int i=1;i<=n;i++)
        st[i][l]=st[st[i][l-1]][l-1];
//处理dis
dis[1]=vec(bs+1,INT_MAX);
for(int l=1;l<=bs;l++)
    for(int i=1;i<=n;i++)
        dis[i][l]=min(dis[i][l-1],dis[st[i][l-1]][l-1]);

//for(vec<int> en:dis){
//    for(int i:en)cout<<i<<" ";
//    cout<<"\len";
//}
function<int(int,int)>get_dis=[&](int x,int y){
    int res=INT_MAX;
    if(deep[x]<deep[y])swap(x,y);
    int lc=deep[x]-deep[y];
//    cout<<x<<" "<<y<<" "<<lc<<"\len";
    for(int l=0;l<=bs&&x!=y;l++)
        if((lc>>l)&1){
            res=min(res,dis[x][l]),x=st[x][l];
//            cout<<x<<" "<<res<<"\len";
        }

    return res;
};
//cout<<get_dis(6,1);
//    return;
function<int(int,int)>lca=[&](int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    int lc=deep[x]-deep[y];
    for(int l=0;l<=bs;l++)if((lc>>l)&1)x=st[x][l];
    if(x==y)return x;
    for(int l=bs;l>=0;l--)
        if(st[x][l]!=st[y][l])
            x=st[x][l],y=st[y][l];
    return st[x][0];
};



//cmp要复用,先写上
function<bool(int,int)>cmp=[&](int a,int b){
    return dfn[a]<dfn[b];
};

int m;
cin>>m;
vec<pii>vf(n+1);
vec<int>vis(n+1,0);
vec<ll>dp(n + 1, 0);
vec<bool>h(n+1, false);
function<void(int)>get_ans=[&](int no){
    if(h[no]){
        h[no]= false;
        dp[vf[no].first]+=vf[no].second;
    }
    else dp[vf[no].first]+=min(dp[no], (ll)vf[no].second);
    //dp[vf[no].first]+=min(dp[no], vf[no].second);
    dp[no]=0;
    vis[vf[no].first]--;
    if(vf[no].first!=1&&vis[vf[no].first]==0)get_ans(vf[no].first);
};
while(m--){
    int k,last=1;
    cin>>k;
    //建虚树
    vec<int>a(k),b;
    for(int &i:a)
        cin>>i,h[i]=true;
    sort(a.begin(),a.end(),cmp);
    b.push_back(1);
    for(int i:a){
        b.push_back(lca(last,i));
        b.push_back(i);
        last=i;
    }
    sort(b.begin(),b.end(),cmp);
    b.erase(unique(b.begin(),b.end()),b.end());
//    for(int i:sum)cout<<i<<" ";
//    cout<<"\len";
    int len=b.size();
//    int len=unique(sum.begin(),sum.end())-sum.begin();
    for(int i=1;i<len;i++){
        int lc=lca(b[i],b[i-1]);
        int d=get_dis(b[i],lc);
       // cout<<d<<"--\len";
        vf[b[i]]={lc,d};
        vis[lc]++;
    }
    //树形dp
    for(int i:b)
        if(vis[i]==0)
            dp[i]=INT_MAX,get_ans(i);
    cout<<dp[1]<<"\n";
    dp[1]=0;
}

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    //cin>>T;
    while (T--) {
        solve();
    }
}
