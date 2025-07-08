
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
///朴素dijkstra算法
///时间复杂是 O(n2+m)O(n2+m), nn 表示点数，mm 表示边数
int g[N][N];  // 存储每条边
int dist[N];  // 存储1号点到每个点的最短距离
bool st[N];   // 存储每个点的最短路是否已经确定
int n;// 点的数量
// 求1号点到n号点的最短路，如果不存在则返回-1
//
int dijkstra(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    //被确定的点最多有n个,第i次确定的点为最短路第i小的点
    for (int i = 0; i < n ; i ++ ){
        int t = -1;     // 在还未确定最短路的点中，寻找距离最小的点
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        // 用t更新其他点的距离
        for (int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], dist[t] + g[t][j]);
        st[t] = true;
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}


///堆优化版dijkstra
///时间复杂度 O(mlogn)O(mlogn), nn 表示点数，mm 表示边数
typedef pair<int, int> PII;
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
// 求1号点到n号点的最短距离，如果不存在，则返回-1
int dijkstra1(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});      // first存储距离，second存储节点编号
    while (heap.size()){
        auto t = heap.top();
        heap.pop();
        int ver = t.second, distance = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver];i; i = ne[i]){
            int j = e[i];
            if (dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}



int main() {
    memset(g,127,sizeof g);


    return 0;
}
