#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
struct node
{
    ll to , nxt , w;
}edge[2000001];
ll head[2000001] , num_edge;
inline void add(ll u , ll v , ll w)
{
    edge[++num_edge].to = v;
    edge[num_edge].w = w;
    edge[num_edge].nxt = head[u];
    head[u] = num_edge;
}
ll fa[3000001] , dep[3000001] , siz[3000001] , son[3000001] , tp[3000001];
ll dfn[3000001] , cnt;
ll s[3000001] , top;
ll n , m , k , a[3000001];
ll mn[3000001];
inline void dfs1(ll x , ll f)
{
    dfn[x] = ++cnt;
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    fa[x] = f;
    for(ll i = head[x] ; i ; i = edge[i].nxt)
    {
        ll v = edge[i].to;
        if(v == f)
        {
            continue;
        }
        mn[v] = min(mn[x] , edge[i].w);
        dfs1(v , x);
        siz[x] += siz[v];
        if(siz[son[x]] < siz[v])
        {
            son[x] = v;
        }
    }
}
inline void dfs2(ll x , ll t)
{
    tp[x] = t;
    if(!son[x])
    {
        return;
    }
    dfs2(son[x] , t);
    for(ll i = head[x] ; i ; i = edge[i].nxt)
    {
        ll y = edge[i].to;
        if(!tp[y])
        {
            dfs2(y , y);
        }
    }
}
inline ll lca(ll x , ll y)
{
    while(tp[x] != tp[y])
    {
        if(dep[tp[x]] < dep[tp[y]])
        {
            swap(x , y);
        }
        x = fa[tp[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
inline ll cmp(ll a , ll b)
{
    return dfn[a] < dfn[b];
}
inline void build()
{
    sort(a + 1 , a + k + 1 , cmp);
    num_edge = 0;
    s[top = 1] = 1;
    s[++top] = a[1];
    fr(i , 2 , k)
    {
        ll l = lca(a[i] , s[top]);
        if(l == s[top])
        {
            continue;
        }
        while(top > 1 && dep[s[top - 1]] >= dep[l])
        {
            add(s[top - 1] , s[top] , 0);
            top--;
        }
        if(l != s[top])
        {
            add(l , s[top] , 0);
            s[top] = l;
        }
        s[++top] = a[i];
    }
    while(top)
    {
        add(s[top - 1] , s[top] , 0);
        top--;
    }
}
inline ll DP(ll x)
{
    if(!head[x])
    {
        return mn[x];
    }
    ll sum = 0;
    for(ll i = head[x] ; i ; i = edge[i].nxt)
    {
        sum += DP(edge[i].to);
    }
    head[x] = 0;
    return min(sum , mn[x]);
}
signed main()
{
    // freopen("in.in" , "r" , stdin);
    // freopen("out.out" , "w" , stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    fr(i , 2 , n)
    {
        ll x , y , z;
        cin >> x >> y >> z;
        add(x , y , z);
        add(y , x , z);
    }
    mn[1] = 2e18;
    dfs1(1 , 0);
    dfs2(1 , 1);
    memset(head , 0 , sizeof(head));
    cin >> m;
    while(m--)
    {
        cin >> k;
        fr(i , 1 , k)
        {
            cin >> a[i];
        }
        build();
        cout << DP(1) << '\n';
    }
    return 0;
}