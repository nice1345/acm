#include<bits/stdc++.h>
using namespace std;
//inline int read(){
//#define num ch-'0'
//    char ch;bool flag=0;int res;
//    while(!isdigit(ch=getchar()))
//        (ch=='-')&&(flag=true);
//    for(res=num;isdigit(ch=getchar());res=res*10+num);
//    (flag)&&(res=-res);
//#undef num
//    return res;
//}
const int N=1e5+5;
const int inf=0x3f3f3f3f;
int v[N*3],loc[N];
bool open[N];
int n,q,cnt,black;
vector<int>g[N];
void dfs(int u,int fa){
    v[++cnt]=-1;
    v[++cnt]=u;
    loc[u]=cnt;
    for(int so:g[u])
        if(so!=fa) dfs(so,u);
    v[++cnt]=-2;
    /*进入加左括号，离开加右括号*/
}
struct seg{
    int l,r,l1,l2,r1,r2,c1,c2,dis;
    void init(int x){
        dis=-inf;
        c1=c2=0;
        if(v[x]==-1) c2=1;
        if(v[x]==-2) c1=1;
        /*c2为失配左括号，c1为失配右括号
        为左括号，c2=1；为右括号，c1=1*/
        if(v[x]>0&&!open[v[x]]) l1= l2= r1= r2=0;
        else l1=l2=r1=r2=-inf;
        /*为黑点，l_plus,l_minus,r_plus,r_minus全为0
        为白点或括号，全为1*/
    }
}tree[N * 12];
inline void merge(seg &s,seg s1,seg s2){
    int a=s1.c1,b=s1.c2,c=s2.c1,d=s2.c2;
    s.dis=max(s1.dis,s2.dis);
    s.dis=max({s.dis,s1.r1+s2.l2,s1.r2+s2.l1});
    b<c?(s.c1=a-b+c,s.c2=d):(s.c1=a,s.c2=b-c+d);
    s.r1=max({s2.r1,s1.r1-c+d,s1.r2+c+d});
    s.r2=max(s2.r2,s1.r2+c-d);
    s.l1=max({s1.l1,s2.l1-b+a,s2.l2+b+a});
    s.l2=max(s1.l2,s2.l2+b-a);
}
void build(int p,int l,int r){
    tree[p].l=l, tree[p].r=r;
    if(l==r){
        tree[p].init(l);
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    merge(tree[p], tree[p << 1], tree[p << 1 | 1]);
}
void modify(int id, int x){
    int l=tree[id].l,r=tree[id].r;
    if(l==r){tree[id].init(l);return;}
    int mid=(l+r)>>1;
    if(x<=mid) modify(id << 1, x);
    else modify(id << 1 | 1, x);
    merge(tree[id], tree[id << 1], tree[id << 1 | 1]);
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;black=n;
    int u,v,x;
    for(int i=1;i<n;++i){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    build(1,1,cnt);
    cin>>q;
    char s;
    while(q--){
        cin>>s;
        if(s=='C'){
            cin>>x;
            if(!open[x]) --black;
            else ++black;
            open[x]^=1;
            modify(1, loc[x]);
        }
        else{
            if(!black) cout<<"-1\n";
            else if(black==1) cout<<"0\n";
            else cout << tree[1].dis << "\n";
        }
    }
    return 0;
}