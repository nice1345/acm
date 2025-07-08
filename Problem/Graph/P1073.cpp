///分层图,虽然能过,但最坏复杂度依然过不去
//#include<bits/stdc++.h>
//using namespace std;
//const int maxn = 1e5 + 5;
//int len, m, d[maxn*3], inq[maxn*3];
//vector<pair<int, int>> G[maxn*3];
//#define t(x,i) (x+i*len)  // t(x,i) 表示第i层的x
//// 建立x->y边的函数, 不用加 make_pair是 C++11特性
//#define updata(x, y) G[t(x,0)].push_back({t(y,0), 0}), G[t(x,1)].push_back({t(y,1),0}), G[t(x,2)].push_back({t(y,2),0})
//void spfa(int s) {
//    for(int i = 1;i <= len*3;i++) d[i] = INT_MIN; // 这里n*3别漏了, INT_MIN 是C++内置最小值常量
//    d[s] = 0;
//    queue<int> Q; inq[s] = true; Q.push(s);
//    while(!Q.empty()) {
//        int x = Q.front(); Q.pop(); inq[x] = false;
//        for(auto [v, len] : G[x])  // C++17 特性, 等价于 int v = G[x][i].first, len = G[x][i].second;
//            if(d[v] < d[x] + len) {
//                d[v] = d[x] + len;
//                if(!inq[v]) { Q.push(v); inq[v] = true; }
//            }
//    }
//}
//int main() {
//    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
//    cin >> len >> m;
//    for(int i = 1, v;i <= len; ++i) {
//        cin >> v;
//        G[t(i,0)].push_back({t(i,1), -v});
//        G[t(i,1)].push_back({t(i,2), v});
//    }
//    for(int i = 1,x,y,z;i <= m; ++i) {
//        cin >> x >> y >> z; updata(x, y);
//        if(z == 2) updata(y, x);
//    }
//    spfa(t(1,0));
//    cout << d[t(len,2)] << endl;
//    return 0;
//}

///复杂度没问题,但不知为何跑的比第一遍的dp慢
#include <bits/stdc++.h>
#define N 100005
#define M 1000005
using namespace std;

int n, m, v[N], minv[N], maxv[N];
int sa[N], ans;
queue <int> q;

struct GRAPH {//图
    int head[N], to[M], nxt[M], cnt = 1;//前向星
    bool toab[N];//能被到达or能到达

    void addedge(int u, int v) {
        to[cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt++;
    }

    void bfs(int s) {//能被到达or能到达 判断
        toab[s] = 1; q.push(s);
        while(q.size()) {
            int p = q.front(); q.pop();
            for(int i = head[p];i;i = nxt[i])
                if(!toab[to[i]])
                    toab[to[i]] = 1, q.push(to[i]);
        }
    }

    void mark(int s, int* a, int v) {//标记其他点信息
        a[s] = v; q.push(s);
        while(q.size()) {
            int p = q.front(); q.pop();
            for(int i = head[p];i;i = nxt[i])
                if(!a[to[i]])//题面保证v>=1，就不必初始化成其他值。
                    a[to[i]] = v, q.push(to[i]);
        }
    }
} mp, fmp;//图和反图

struct OP {//点排序规则
    bool operator() (int a, int b) const {
        return v[a] < v[b];
    }
};

int main() {
    scanf("%d%d", &n, &m);
    int a, b, op;
    for(int i = 1;i <= n;i++)
        scanf("%d", v + i);
    while(m--) {
        scanf("%d%d%d", &a, &b, &op);
        mp.addedge(a, b);
        fmp.addedge(b, a);
        if(op == 2) {//存图
            mp.addedge(b, a);
            fmp.addedge(a, b);
        }
    }
    mp.bfs(1); fmp.bfs(n);//能被到达or能到达 执行判断
    for(int i = 1;i <= n;i++) sa[i] = i;
    sort(sa + 1, sa + n + 1, OP());
    for(int i = 1;i <= n;i++)//标记minv
        if(!minv[sa[i]] && mp.toab[sa[i]])//能被起点到达 且 没被标记
            mp.mark(sa[i], minv, v[sa[i]]);
    for(int i = n;i;i--)//标记maxv
        if(!maxv[sa[i]] && fmp.toab[sa[i]])//能到达终点 且 没被标记
            fmp.mark(sa[i], maxv, v[sa[i]]);
    /*=================调试用=================
    puts("ok now");
    for(int i = 1;i <= len;i++)
        printf("%d: max: %d min: %d\len", i, maxv[i], minv[i]);
    puts("");
    ===================调试用=================*/
    for(int i = 1;i <= n;i++)//更新答案
        if(mp.toab[i] && fmp.toab[i])//存在合法路径
            ans = max(ans, maxv[i] - minv[i]);//尝试更新答案
    printf("%d", ans);
    return 0;
}