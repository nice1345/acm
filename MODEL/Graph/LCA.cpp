#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define ll long long
#define pii pair<int,int>
#define vec vector
const int N = 200005;
int mod =  998244353;
//rmq写法，查询复杂度O(1),写虚树时建议的写法，因为已经预处理出dfn
void solve1(){
    int n,root,m;cin>>n>>m>>root;
    vec<vec<int>>g(n+1,vec<int>(0));
    for(int i=1;i<n;i++){
        int u,v;
        cin>>v>>u;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vec<int>idx(n+1,0),deep(n+1,0),f(n+1);
    int cnt=0;
    int maxlg=__lg(n);
    vec<vec<int>>rmq(n+1,vec<int>(maxlg+1));
    vec<int>lg(n+1,0),po(maxlg+1,0);
    for(int i=0;i<=maxlg;i++)lg[1<<i]=i,po[i]=(1<<i);
    for(int i=3;i<=n;i++)
        if(lg[i]==0)
            lg[i]=lg[i-1];
    function<void(int,int)>get_dfn=[&](int no,int fa){
        idx[no]=++cnt;
        rmq[cnt][0]=no;
        deep[no]=deep[fa]+1;
        f[no]=fa;
        for(int so:g[no]){
            if(so==fa)continue;
            get_dfn(so,no);
        }
    };
    get_dfn(root,0);
    for(int len=1;len<=maxlg;len++){
        for(int i=1;i+po[len]-1<=n;i++){
            int r1=rmq[i][len-1],r2=rmq[i+po[len-1]][len-1];
            rmq[i][len]=(deep[r1]<deep[r2])?r1:r2;
        }
    }
    function<int(int,int)>get_lca=[&](int x,int y){
        if(x==y)return x;
        if(idx[x]>idx[y])swap(x,y);
        int ml=lg[idx[y]-idx[x]];
        int r1=rmq[idx[x]+1][ml],r2=rmq[idx[y]-po[ml]+1][ml];
        return (deep[r1]<deep[r2])?f[r1]:f[r2];
    };
    while(m--){
        int q,w;
        cin>>q>>w;
        cout<<get_lca(q,w)<<"\n";
    }
}
//树刨，预处理O(n),查询最大O(log(n)),一般的数据查询都远小于log(n),平均可能只有O(5~10)
void solve(){
    int n,root,m;cin>>n>>m>>root;
    vec<vec<int>>g(n+1,vec<int>(0));
    int u,v;
    for(int i=1;i<n;i++){
        cin>>v>>u;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vec<int>f(n+1),sum(n+1),top(n+1),deep(n+1);
    function<void(int,int)>get_sum=[&](int no,int fa){
        sum[no]=1;
        f[no]=fa;
        deep[no]=deep[fa]+1;
        for(int so:g[no]){
            if(so==fa)continue;
            get_sum(so,no);
            sum[no]+=sum[so];
        }
    };
    get_sum(root,0);
    function<void(int,int)>get_top=[&](int no,int to){
        top[no]=to;
        int ma=0,ms=0;
        for(int so:g[no]){
            if(so==f[no])continue;
            if(ma<sum[so]){
                ms=so;
                ma=sum[so];
            }
        }
        for(int so:g[no]){
            if(so==f[no])continue;
            if(so==ms)get_top(so,to);
            else get_top(so,so);
        }
    };
    get_top(root,root);
    function<int(int,int)>get_lca=[&](int x,int y){
        while(top[x]!=top[y]){
            if(deep[top[x]]<deep[top[y]])swap(x,y);
            x=f[top[x]];
        }
        if(deep[x]<deep[y])swap(x,y);
        return y;
    };
    while(m--){
        int q,w;cin>>q>>w;
        cout<<get_lca(q,w)<<"\n";
    }
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    //cin>>_;
    for(int i=1;i<=_;i++){
        solve1();
    }
    return 0;
}

