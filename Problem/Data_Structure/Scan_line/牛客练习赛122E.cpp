#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
#define vec vector
const int N=1e5+5;
int n,m,u,v,cnt=0;
vec<int>g[N];
int dfn[N],en[N],inv[N];
void dfs(int no,int fa){
    dfn[no]=++cnt;
    inv[cnt]=no;
    for(int so:g[no]){
        if(so==fa)continue;
        dfs(so,no);
    }
    en[no]=cnt;
}
/**
妙啊
  1   -1
q i w
 l  r
 * */

int main() {
cin>>n>>m;
for(int i=1;i<n;i++){
    cin>>u>>v;
    g[u].push_back(v);
    g[v].push_back(u);
}
dfs(1,0);



return 0;
}

