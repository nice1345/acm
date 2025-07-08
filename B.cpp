#include <iostream>
#include<time.h>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<deque>
#include<set>
#include<stack>
#include<algorithm>
#include <cstdio>
#include <cstring>
#include<cmath>
#include <vector>
#include <map>
#include <stack>
#include<queue>
using namespace std;
using ll =long long;
const int N=(int)5e5+5;
ll mod=(long)1e9+7;
int t,n,m,root,q,w;
int last[N*2],go[N*2],now[N],f[N][20],d[N],cnt;
set<int>myson[N];
ll qmi(ll a,ll b){
    ll res=1,p=a;
    while (b){
        if(b&1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}

int extended_euclid(int a,int b,int &x,int &y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    int res= extended_euclid(b,a%b,y,x);
    y-=a/b*x;
    return res;
}

void add(int u,int v){
    last[++cnt]=now[u];
    now[u]=cnt;
    go[cnt]=v;
 // cout<<last[cnt]<<" "<<now[u]<<" "<<go[cnt]<<" "<<u<<" "<<v<<endl;
}

void dfs(int fa,int no){
    d[no]=d[fa]+1;
    f[no][0]=fa;
    for(int i=1;d[no]>(1<<i);i++){
        f[no][i]=f[f[no][i-1]][i-1];
    }
    for(int i=now[no];i;i=last[i]){
        int so=go[i];
        if(so==fa)continue;
        dfs(no,so);
    }
}

int LCA(int x,int y){
    if(d[x]<d[y])swap(x,y);
    for(int i=19;d[x]>d[y];i--)
        if(d[x]-(1<<i)>=d[y])
            x=f[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)
        if(d[x]>(1<<i)&&f[x][i]!=f[y][i]){
            x=f[x][i];y=f[y][i];
        }
    return f[x][0];
}

int gcd(int a,int b){return b?gcd(b,b%a):a;}

void solve(){
    scanf("%d%d%d",&n,&m,&root);
    for(int i=1;i<n;i++){
        scanf("%d%d",&q,&w);
        add(q,w);
        add(w,q);
    }
    dfs(0,root);
    while (m--){
        scanf("%d%d",&q,&w);
        printf("%d\n", LCA(q,w));
    }
}


int main() {
    //scanf("%d",&t);
    t=1;
    while (t--){
        solve();
    }
    return 0;
}
