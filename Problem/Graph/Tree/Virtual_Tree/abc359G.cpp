#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define ll long long
#define pii pair<int,int>
#define vec vector
const int N = 200005;
int mod =  998244353;
void solve(){
    int n;cin>>n;
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
    get_dfn(1,0);
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
    map<int,vec<int>>h;
    vec<int>id(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>id[i];
        h[id[i]].emplace_back(i);
    }
    vec<vec<pii>>e(n+1,vec<pii>(0));
    int ans=0;
    vec<int>son_sum(n+1,0),dis(n+1,0);
    for(auto [val,j]:h){
        sort(j.begin(),j.end(),[&](int a,int b){
            return idx[a]<idx[b];
        });
        vec<int>din;int last=1;
        din.emplace_back(1);
        for(int i:j){
            din.emplace_back(get_lca(last,i));
            din.emplace_back(i);
            last=i;
        }
        sort(din.begin(),din.end(),[&](int a,int b){
            return idx[a]<idx[b];
        });
        din.erase(unique(din.begin(),din.end()),din.end());
        last=din.size();
        for(int i=1;i<last;i++){
            int lc=get_lca(din[i],din[i-1]);
            e[lc].emplace_back(din[i],(deep[din[i]]-deep[lc]));
        }
        function<void(int,int,int)>cal=[&](int no,int fa,int di){
            son_sum[no]=(id[no]==val)?1:0;
            dis[no]=0;
            for(auto [so,wo]:e[no])
                cal(so,no,wo);
            son_sum[fa]+=son_sum[no];
            dis[fa]+=dis[no]+son_sum[no]*di;
        };
        function<void(int,int,int)>get_ans=[&](int no,int fa,int di){
            dis[no]=dis[fa]+((int)j.size()-son_sum[no]*2ll)*di;
            if(id[no]==val)ans+=dis[no];
            for(auto [so,wo]:e[no])
                get_ans(so,no,wo);
        };
        cal(1,0,0);
        if(id[1]==val)ans+=dis[1];
        for(auto [so,wo]:e[1])
            get_ans(so,1,wo);
        son_sum[0]=0;
        dis[0]=0;
        for(int i:din)e[i].clear();
    }
    cout<<ans/2ll<<"\n";
}
signed main()
{
    //freopen("D:\\CLionProject\\untitled\\r.txt","r",stdin); //输入重定向，输入数据将从r.txt文件中读取
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    //cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

