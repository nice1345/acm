/**
 题目链接：https://www.luogu.com.cn/problem/P2163
 题解：https://blog.csdn.net/qq_45458915/article/details/119868279
 主席树和扫描线都是可以的
 * */
#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
template<typename T>
inline void read(T &x)
{
    T f=1;x=0;
    char ch=getchar();
    while(0==isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(0!=isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    x*=f;
}
template<typename T>
inline void write(T x)
{
    if(x<0){x=~(x-1);putchar('-');}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int inf=0x3f3f3f3f;
const int N=1e7+100;
struct Node {
    int x,y,type,op,id;
    bool operator<(const Node& t)const {
        if(x!=t.x) {
            return x<t.x;
        } else {
            return type<t.type;
        }
    }
};
vector<Node>node;
int ans[N],c[N];
void add(int x) {
    for(int i=x;i<N;i+=lowbit(i)) c[i]++;
}
int ask(int x) {
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)) ans+=c[i];
    return ans;
}
int main()
{
    int n,m;
    read(n),read(m);
    for(int i=1,x,y;i<=n;i++) {
        read(x),read(y);
        x++,y++;
        node.push_back({x,y,0,-1,-1});
    }
    for(int i=1,x1,x2,y1,y2;i<=m;i++) {
        read(x1),read(y1),read(x2),read(y2);
        x1++,x2++,y1++,y2++;
        node.push_back({x2,y2,1,1,i});
        node.push_back({x1-1,y1-1,1,1,i});
        node.push_back({x1-1,y2,1,-1,i});
        node.push_back({x2,y1-1,1,-1,i});
    }
    sort(node.begin(),node.end());
    for(auto it:node) {
        if(it.type==1) {//ask
            ans[it.id]+=it.op*ask(it.y);
        } else {//updata
            add(it.y);
        }
    }
    for(int i=1;i<=m;i++) {
        //printf("%d\len",sum[i]);
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}
