#include <bits/stdc++.h>
#define vec vector
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;



int main() {
cin.tie(0)->sync_with_stdio(0);
int n,m,u,v;
cin>>n>>m;
vec<vec<int>>g(n+1);
vec<int>f(n+1),pre(n+1,0),suf(n+1,n+1);
for(int i=0;i<n-1;i++){
    cin>>u>>v;
    g[u].push_back(v);
    g[v].push_back(u);
}
function<void(int,int)>get_f=[&](int no,int fa){
    f[no]=fa;
    for(int so:g[no]){
        if(so==fa)continue;
        get_f(so,no);
    }
};
get_f(1,0);


return 0;
}
