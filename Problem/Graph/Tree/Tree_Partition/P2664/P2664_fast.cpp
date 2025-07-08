#include<bits/stdc++.h>
using namespace std;
struct edge
{
    int to,nxt;
}e[200005];
int h[100005],tree[100005],dfn[100005],siz[100005],colsiz[100005],cnt;
long long cf[100005],dep[100005];
bool buc[100005];
vector<int>v[100005];
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x;
}
void write(long long x)
{
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}
inline void adde(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].nxt=h[x];
    h[x]=cnt;
}
void dfs(int x,int f)
{
    siz[x]=1;
    dfn[x]=++cnt;
    for(int i=h[x];i;i=e[i].nxt)
        if(e[i].to!=f){
            int psiz=colsiz[tree[x]];//记录下递归前的个数
            dfs(e[i].to,x);
            siz[x]+=siz[e[i].to];
            int nsiz=siz[e[i].to]+psiz-colsiz[tree[x]];//此处意为siz[e[i].to]-(colsiz[tree[x]]-psiz)
            colsiz[tree[x]]+=nsiz;
            cf[e[i].to]+=nsiz;//打上加的标记
            while(v[tree[x]].size() && dfn[v[tree[x]].back()] > dfn[x])//从后往前找
            {
                cf[v[tree[x]].back()]-=nsiz;
                v[tree[x]].pop_back();
            }
        }
    colsiz[tree[x]]++;
    v[tree[x]].push_back(x);
}
void dfs2(int x,int f)//根据差分数组计算最终答案
{
    dep[x]=dep[f]+cf[x];
    for(int i=h[x];i;i=e[i].nxt)
        if(e[i].to!=f)
            dfs2(e[i].to,x);
}
int main()
{
    int n=read(),m=0,tot=0,i,x,y;
    for(i=1;i<=n;i++)
    {
        tree[i]=read();
        m=max(m, tree[i]);
        buc[tree[i]]=true;//记录一个颜色是否出现在a[i]中
    }
    for(i=1;i<n;i++)
    {
        x=read();
        y=read();
        adde(x,y);
        adde(y,x);
    }
    cnt=0;
    dfs(1,0);
    for(i=1;i<=m;i++)//处理包含1的那些连通块
        if(buc[i])
        {
            tot++;
            cf[1]+=n-colsiz[i];
            for(int j=0;j<v[i].size();j++)
                cf[v[i][j]]-=n-colsiz[i];
        }
    dfs2(1,0);
    for(i=1;i<=n;i++)
    {
        write(1ll*n*tot-dep[i]);
        putchar('\n');
    }
    return 0;
}