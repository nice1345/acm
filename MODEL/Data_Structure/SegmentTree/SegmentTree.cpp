
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ll long long
#define vec vector
#define pii array<int,2>
const int N = 1000005;
ll mod = (ll) 998244353;
/*
 区修区改线段树
 */
struct segmentTree{
    struct node{
        int sum=0,lazy=0;
    };
    vec<node>tree;
    int n;
    segmentTree(int &len){
        tree.resize(len*4+5);
        n=len;
    }
    segmentTree(vec<int> &a){
        n=a.size();
        tree.resize(n*4+5);
        function<int(int,int,int)>build=[&](int id,int l,int r){
            if(l==r){
                tree[id].sum=a[l];
                return a[l];
            }
            int mid=(l+r)>>1;
            tree[id].sum=build(id<<1,l,mid)+build(id<<1|1,mid+1,r);
            return tree[id].sum;
        };
        build(1,0,n);
    }
    int update(int id,int l,int r,int ql,int qr,int val){
        if(r<ql||qr<l){}
        else if(ql<=l&&r<=qr)
            tree[id].lazy+=val;
        else{
            int mid=(l+r)>>1;
            tree[id].sum= update(id<<1,l,mid,ql,qr,val)+update(id<<1|1,mid+1,r,ql,qr,val);
        }
        return (r-l+1)*tree[id].lazy+tree[id].sum;
    }
    int query(int id,int l,int r,int ql,int qr){
        if(r<ql||qr<l)return 0;
        else if(ql<=l&&r<=qr)
            return (r-l+1)*tree[id].lazy+tree[id].sum;
        else{
            tree[id].sum+=tree[id].lazy*(r-l+1);
            tree[id<<1].lazy+=tree[id].lazy;
            tree[id<<1|1].lazy+=tree[id].lazy;
            tree[id].lazy=0;
            int mid=(l+r)>>1;
            return query(id<<1,l,mid,ql,qr)+ query(id<<1|1,mid+1,r,ql,qr);
        }
    }
    void modify(int l,int r,int val){
        update(1,0,n,l,r,val);
    }
    int getSum(int l,int r){
        return query(1,0,n,l,r);
    }
};
void solve() {

}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }

    return 0;
}
