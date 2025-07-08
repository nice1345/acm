#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
/** dfs求重心
树的重心如果不唯一，则至多有两个，且这两个重心相邻。
以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。
树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。
把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。
在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。

 求法：枚举以每个节点为根时，最大的子树的节点是否不超过整棵树大小的一半
 * */
int n;
vector<int>son[N];
vector<int>ans;
int sum[N];//以某个节点为根时，该节点形成的子树的大小
int weight[N];//以该节点为根时，最大子树的大小

void dfs(int no,int fa){
    sum[no]=1;
    weight[no]=0;
    for(int so:son[no]){
        if(so==fa)continue;
        dfs(so,no);
        sum[no]+=sum[so];
        weight[no]= max(weight[no],sum[so]);
    }
    weight[no]= max(weight[no],n-sum[no]);
    if(weight[no]<=n/2)ans.push_back(no);
}




int main() {
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}
