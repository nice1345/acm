#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1000005;
ll mod=(ll)1e9+7;

ll qmi(ll a,ll b){
    ll res=(ll)1,p=a%mod;
    while (b){
        if(b&(ll)1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}
int T;
int n,k;
int last[N*2],go[N*2],now[N*2],cnt=0;
ll dis[N],su[N],mm=0;
void add(int u,int v){
    last[++cnt]=now[u];
    now[u]=cnt;
    go[cnt]=v;
}
void dfs(int no,int fa){
//    printf("%d %d---\len",no,fa);
    for(int i=now[no];i;i=last[i]){
        if(go[i]!=fa)dfs(go[i],no);
    }
    su[no]++;
    su[fa]+=su[no];
    dis[fa]=(dis[fa]+dis[no]+su[no]);
}
void dfs1(int no,int fa){
    if(no!=1)  dis[no]=(dis[fa]-su[no]+(ll)n-su[no]);
    mm=(mm+dis[no]%mod)%mod;
    for(int i=now[no];i;i=last[i]){
        if(go[i]!=fa)dfs1(go[i],no);
    }
}
//ll sz[N],sum;
//void dfs2(int no,int fa){
//    sz[no]=1;
//    for(int i=now[no];i;i=last[i]){
//        if(go[i]==fa)continue;
//        test(go[i],no);sz[no]+=sz[go[i]];
//        sum=(sum+sz[go[i]]*((ll)len-sz[go[i]])%mod)%mod;
//    }
//}

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    if(k&1)puts("1");
    else{
       // 法一求距离(求出每个点到所有点的距离,相加除2)
        dfs(1,0);dfs1(1,0);
        printf("%lld",(mm*qmi((ll)n*(ll)(n-1)%mod,mod-2)%mod+(ll)1)%mod);



    }
    return 0;
}


