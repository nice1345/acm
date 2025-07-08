#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,u,v;
int sg[N];
vector<int>g[N];
void dfs(int no,int fa){
    for(int so:g[no]){
        if(so==fa)continue;
        dfs(so,no);
        sg[no]^=(sg[so]+1);
    }
}
int main(){
    int _;cin>>_;
    while(_--){
        cin>>n;
        for(int i=1;i<=n;i++){
            g[i].clear();
            sg[i]=0;
        }
        for(int i=1;i<n;i++){
            cin>>u>>v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        dfs(1,0);
        cout<<((sg[1]>0)?"Alice":"Bob")<<"\n";
    }
    return 0;
}
