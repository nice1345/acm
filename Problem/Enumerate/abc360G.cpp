#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
const int N = 2e5 + 5;
const int mod = 998244353;
//const int mod =1e9+7;
/**
  pre[i] a[i]结尾的上升序列
  suf[i] a[i]开头的上升序列
 假设答案是修改位置在i~j
 pre[i]+1+suf[j]
 suf[j]-pre[i]>1;
 j-i>1
 只需枚举pre[i]
 * */
struct MaxSegmentTree{
    vec<int>tree;
    int len;
    MaxSegmentTree(int &n){tree.resize(n*4+40);len=n+5;}
    void update(int id,int l,int r,int q,int val){
        if(l==r){tree[id]=max(tree[id],val);return;}
        int mid=(l+r)>>1;
        if(q<=mid)update(id<<1,l,mid,q,val);
        else update(id<<1|1,mid+1,r,q,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    int query(int id,int l,int r,int ql,int qr){
        if(r<ql||qr<l)return 0;
        else if(ql<=l&&r<=qr)return tree[id];
        else {
            int mid=(l+r)>>1;
            return max(query(id<<1,l,mid,ql,qr),query(id<<1|1,mid+1,r,ql,qr));
        }
    }
    void modify(int ql,int val){ update(1,0,len,ql,val);}
    int getMax(int ql,int qr){return query(1,0,len,ql,qr);}
};
void solve() {
int n;cin>>n;
vec<int>a(n+1),b,c(n+1);
for(int i=1;i<=n;i++)cin>>a[i],b.emplace_back(a[i]),b.emplace_back(a[i]+1);
if(n==1){cout<<"1";return;}
sort(b.begin(),b.end());
b.erase(unique(b.begin(),b.end()),b.end());
int len=b.size(),id;
MaxSegmentTree suf(len),pre(len);
int ans=1;
for(int i=n;i>2;i--){
    id=lower_bound(b.begin(), b.end(),a[i])-b.begin()+1;
    suf.modify(id,suf.getMax(id+1,len)+1);
    id=lower_bound(b.begin(), b.end(),a[i-2])-b.begin()+1;
    c[i-2]=suf.getMax(id+2,len+2);
}
id=lower_bound(b.begin(), b.end(),a[2])-b.begin()+1;
suf.modify(id,suf.getMax(id+1,len)+1);
ans=max(ans,suf.getMax(1,len)+1);
id=lower_bound(b.begin(), b.end(),a[1])-b.begin()+1;
suf.modify(id,suf.getMax(id+1,len)+1);
ans=max(ans,suf.getMax(1,len));
for(int i=1;i<n-1;i++){
    id=lower_bound(b.begin(), b.end(),a[i])-b.begin()+1;
    int mi=pre.getMax(0,id-1)+1;
    pre.modify(id,mi);
    ans=max(ans,c[i]+mi+1);
}
id=lower_bound(b.begin(), b.end(),a[n-1])-b.begin()+1;
pre.modify(id,pre.getMax(0,id-1)+1);
ans=max(ans,pre.getMax(1,len)+1);
cout<<ans;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    //cin>>T;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
