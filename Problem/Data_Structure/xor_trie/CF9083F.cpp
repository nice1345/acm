#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define vec vector
const int N = 2e5 + 5;
const int mod = 998244353;
struct node{
    array<int,2>son;
    int id;
};
struct trie{
    vec<node>tree;
    int cnt=0;
    trie(){
        tree.push_back({0,0,0});

    }
    void insert(int val,int idx){
        int p=0,op;
        for(int i=29;i>=0;i--){
            if(val&(1<<i))op=1;
            else op=0;
            if(!tree[p].son[op]){
                tree.push_back({0,0,0});
                tree[p].son[op]=++cnt;
            }
            p=tree[p].son[op];
            tree[p].id=max(tree[p].id,idx);
            //cout<<i<<" "<<p<<" "<<op<<" "<<tree[p].id<<"\n";
        }
    }
    int query(int val,int ma){
        int p=0,op,nxt,res=0,no,flag=0;
        for(int i=29;i>=0;i--){
            if(ma&(1<<i))op=1;
            else op=0;
            if(val&(1<<i))no=1;
            else no=0;
            nxt=no^op;
            //cout<<i<<" "<<op<<" "<<no<<" "<<nxt<<" "<<tree[p].son[nxt^1]<<"\n";
            if(op==1&&tree[p].son[nxt^1]!=0)
                res=max(res,tree[tree[p].son[nxt^1]].id);
            if(tree[p].son[nxt]!=0)
                p=tree[p].son[nxt];
            else break;
            flag++;
        }
        if(flag==30)res=max(res,tree[p].id);
        //cout<<res<<"\n";
        return res;
    }
};
/*
 二分值
 枚举区间右边界，左边界最大的值
 当前枚举到r，l为(1-r-1里面a[l]^a[r]<=val的最大下标
 以及所有右边界小于r的区间的左边界最大值(就是之前根据r查询到的最大左边界))的最大下标
 * */
void solve() {
    int n,k;cin>>n>>k;
    vec<int>a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    function<bool(int)>ch=[&](int val){
        int ma=0,ne,sum=0;
        trie tree;
        for(int i=1;i<=n;i++){
            ma=max(ma,tree.query(a[i],val));
            sum+=ma;
            //if(val==9)cout<<tree.query(a[i],val)<<"\n";
            tree.insert(a[i],i);
        }
        //cout<<val<<" "<<sum<<"\n";
        if(sum>=k)return true;
        return false;
    };
    int l=0,r=pow(2,30)-1ll,mid;
    while(l<r){
        mid=(l+r)>>1;
        if(ch(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<"\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
