#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll mod=(ll)998244353;
const int N=5e5+5;
/**
 dfs生成树剩下的边(没有被生成树选中的边)全是返祖边或者前向边，不会出现横叉边
 * */

int n,m,col[N];//col用来记录深度奇偶性，-1表示灰色的边
vector<pair<int,int> > a[N];//用pair存图 点 边的编号
bool v[N];//标记数组
//dfs生成树
void dfs(int u,int y){
    v[u]=1;//标记
    for(auto [x,z]:a[u]){
        if(v[x]) continue;//如果点以及遍历过了那么直接跳过
        col[z]=y;//否则便通过奇偶性存下
        dfs(x,y^1);
    }
}
void solve() {
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].push_back({v,i});
        a[v].push_back({u,i});
        col[i]=-1;//初始化全是灰色
    }
    for(int i=1;i<=n;i++)
        if(!v[i])
            dfs(i,1);//没走过的点就搜一下


    for(int i=1;i<=m;i++)
        switch (col[i]) {
            case -1:
                cout<<'G';break;
            case 0:
                cout<<'R';break;
            case 1:
                cout<<'B';break;
        }


}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    for(int _=1;_<=T;_++){
        solve();
    }



    return 0;
}