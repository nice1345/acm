#include<bits/stdc++.h>
using namespace std;
#define vec vector
#define vi vec<int>
#define vb vec<bool>
#define vbi vec<basic_string<int>>
#define bi basic_string<int>
const int N = 2e5+5;
const int mod =  998244353;
//const int mod =1e9+7;
/**
 官解有点怪
 存在欧拉回路除了要保证每个点的度数为偶数，还要保证图联通
 官解没有保证图联通，可能是题目中保证了什么条件
 思路就是通过删除边将每个点度数化为偶数，在暴力查找
 重点思路就是dfs生成树那的树形dp

 还有一种复杂的思路 cup-pyy
 将生成树上的奇度数点两两配对，并标记其路径上的边
 被标记为奇数次的边就删去，偶数次留下，也能保证奇偶性
 * */
void solve() {
    int n,m;cin>>n>>m;
    //边的编号
    vi edge(m);
    //全图和只包含黑边的图
    vbi g(n+1,bi()),black(n+1,bi());
    for(int i=0;i<m;i++){
        int x, y, c;cin >> x >> y >> c;x--;y--;
        edge[i] = x ^ y;g[x]+=i;g[y]+=i;
        if (c == 0) {black[x]+=i;black[y]+=i;}
    }
    //统计每个点的奇偶性
    vb degree(n);for(int i=0;i<n;i++)degree[i]=(int)g[i].size()&1;
    //记录每个点的访问状态       每条边的删除情况
    vb vis(n,0),del(m, 0);int dis=0;
    //类似于树形dp
    //先将底层的节点变成偶度数节点，一层一层往上递归，所以先dfs在处理节点
    //返祖边从父节点删除，也可以看作删除前向边
    //这样保证除了根部以外的节点都能处理为偶度数
    function<void(int)>dfs=[&](int no){
        vis[no]=true;
        for(int id:black[no]){
            int to=edge[id]^no;
            if(vis[to])continue;
            //从深处处理，先dfs
            dfs(to);
            //子节点的子节点又子节点处理完了，就处理子节点
            if(degree[to]){
                del[id]=true;dis++;
                degree[to]=false;
                degree[no]=!degree[no];
            }
        }
    };
    for(int i=0;i<n;i++){
        if(!vis[i])dfs(i);
        if(degree[i]){
            cout << "NO\n";
            return;
        }
    }
    function<void(int)> euler = [&]( int u) {
        while (!g[u].empty()) {
            int id = g[u].back();
            g[u].pop_back();
            int to = edge[id] ^ u;
            if (del[id]) continue;
            del[id] = true;
            euler(to);
        }
        cout << u + 1 << ' ';
    };
    cout << "YES\n";
    cout << m - dis << '\n';
    euler( 0);
    cout << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

