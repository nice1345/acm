/**
 题目链接：https://www.luogu.com.cn/problem/P1972
 题解：https://www.luogu.com.cn/article/boho8rhn
 此题可以用主席树解，但扫描线树状数组更好写
对于若干个询问的区间[l,r]，如果他们的r都相等的话，那么项链中出现的同一个数字，一定是只关心出现在最右边的那一个的，例如：

项链是：1 3 4 5 1

那么，对于r=5的所有的询问来说，第一个位置上的1完全没有意义，因为r已经在第五个1的右边，对于任何查询的[L,5]区间来说，如果第一个1被算了，那么他完全可以用第五个1来替代。

因此，我们可以对所有查询的区间按照r来排序，然后再来维护一个树状数组，这个树状数组是用来干什么的呢？看下面的例子：

1 2 1 3

对于第一个1，insert(1,1)；表示第一个位置出现了一个不一样的数字，此时树状数组所表示的每个位置上的数字（不是它本身的值而是它对应的每个位置上的数字）是：1 0 0 0

对于第二个2，insert(2,1)；此时树状数组表示的每个数字是1 1 0 0

对于第三个1，因为之前出现过1了，因此首先把那个1所在的位置删掉insert(1,-1),然后在把它加进来insert(3,1)。此时每个数字是0 1 1 0

如果此时有一个询问[2,3]，那么直接求sum(3)-sum(2-1)=2就是答案。
 * */
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000010
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
int n,m;
int a[maxn],ans[maxn];
int vis[maxn],tree[maxn];
struct QUE{
    int l;
    int r;
    int id;
}q[maxn];
inline bool cmp(const QUE &a,const QUE &b){
    return a.r<b.r;
}

inline int lowbit(int x){
    return x&(-x);
}

void modify(int p,int v){
    for(;p<=n;p+=lowbit(p))
        tree[p]+=v;
}

int query(int p){
    int res=0;
    for(;p;p-=lowbit(p))
        res+=tree[p];
    return res;
}

int main(){
    read<int>(n);
    for(int i=1;i<=n;++i) read<int>(a[i]);
    read<int>(m);
    for(int i=1;i<=m;++i){
        read<int>(q[i].l); read<int>(q[i].r); q[i].id=i;
    }
    sort(q+1,q+m+1,cmp);

    int pow=1;
    for(int i=1;i<=m;++i){
        for(int j=pow;j<=q[i].r;++j){
            if(vis[a[j]]) modify(vis[a[j]],-1);
            modify(j,1);
            vis[a[j]]=j;
        }
        pow=q[i].r+1;
        ans[q[i].id]=query(q[i].r)-query(q[i].l-1);
    }

    for(int i=1;i<=m;++i) {
        //printf("%d\n",ans[i]);
        write<int>(ans[i]);
        putchar('\n');
    }
    return 0;
}