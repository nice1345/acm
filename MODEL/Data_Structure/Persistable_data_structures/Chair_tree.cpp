//P3834求静态区间第k小
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = (ll) 998244353;
const int N = 100005;
int top=0,n,l,m;
int tree[64*N],pr[N],ls[64*N],rs[64*N];
//建树
int build(int l,int r){
    int now=++top;
    if(l==r)return now;
    int mid=(l+r)>>1;
    ls[now]=build(l,mid);
    rs[now]=build((mid+1),r);
    return now;
}
//k是要插入的值,l,r是当前区间的范围,pre是当前范围的区间的前一个历史版本的节点编号
int moify(int k,int l,int r,int pre){
    int now=++top;
    //因为插入了k,当前版本的节点的数的数量肯定是上一个历史版本的的节点的数的数量+1
    tree[now]=tree[pre]+1;
    //复制上一个历史版本的左右儿子信息
    ls[now]=ls[pre];rs[now]=rs[pre];
    //已经到了叶子节点,不用继续更新了
    if(l==r)return now;
    int mid=(r+l)>>1;
    //k要插入到哪个儿子就更新哪个
    if(k<=mid) ls[now]=moify(k,l,mid,ls[pre]);
    else rs[now]=moify(k,(mid+1),r,rs[pre]);
    return now;
}
//设要查询[i+1,j]第k小
//l,r是当前遍历到的范围,lr是第i版本中改范围的节点编号,rr是第j版本中改范围的节点编号
//tree[ls[rr]]-tree[ls[lr]]就是区间[i+1,j]内,大小在[l,r]的数的数量
int query(int lr,int rr,int l,int r,int k){
    if(l==r)//叶子节点一定是答案,到了叶子节点就返回
        return l;
    //用第qr次更新的版本减去第ql-1次的历史版本得到我们所需要的[ql,qr]的左儿子的版本的数量
    int lsum=tree[ls[rr]]-tree[ls[lr]];
    int mid=(l+r)>>1;
    if(k<=lsum)//小于就在左儿子这边
        return query(ls[lr],ls[rr],l,mid,k);
    else //大于就在右儿子这边，减去左儿子的数量继续判
        return query(rs[lr],rs[rr],(mid+1),r,(k-lsum));
}

int main() {
    scanf("%d%d",&n,&m);
    vector<int>a(n),b(n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);b[i]=a[i];
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    l=b.size()-1;
    pr[0]= build(0,l);
    for(int i=0;i<n;i++){
        //离散化后插入的是名次,从0开始
        int kk=(lower_bound(b.begin(),b.end(),a[i])-b.begin());
        pr[i+1]= moify(kk,0,l,pr[i]);
    }
    for(int i=0;i<m;i++){
        int ql,qr,k;
        scanf("%d%d%d",&ql,&qr,&k);
        printf("%d\n",b[query(pr[ql-1],pr[qr],0,l,k)]);
    }
    return 0;
}
