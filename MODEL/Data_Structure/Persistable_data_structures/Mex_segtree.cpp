#include<bits/stdc++.h>
using namespace std;

struct mex_segtree{
    struct node{int ls=0,rs=0,mi=0;};
    vector<node>tree;
    vector<int>root;
    int cnt=0,sum=0,bound;
    int build(int l,int r){
        int id=++cnt;
        if(l==r)return id;
        int mid=(l+r)>>1;
        tree[id].ls=build(l,mid);
        tree[id].rs=build(mid+1,r);
        return id;
    }
    mex_segtree(int n,int ma){
        bound=ma+3;
        root.resize(n+1);
        tree.resize(bound*25);
        root[0]= build(0,bound);
    }
    void update(int nr,int cr,int l,int r,int loc,int v){
        tree[cr]=tree[nr];
        if(l==r){tree[cr].mi=v;return;}
        int mid=(l+r)>>1;
        if(loc<=mid){tree[cr].ls=++cnt;update(tree[nr].ls,cnt,l,mid,loc,v);}
        else{tree[cr].rs=++cnt;update(tree[nr].rs,cnt,mid+1,r,loc,v);}
        tree[cr].mi=min(tree[tree[cr].ls].mi,tree[tree[cr].rs].mi);
    }
    int query(int cur,int last,int l,int r){
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(tree[tree[cur].ls].mi<last)return query(tree[cur].ls,last,l,mid);
        else return query(tree[cur].rs,last,mid+1,r);
    }
    void add(int v){
        sum++;
        root[sum]=++cnt;
        update(root[sum-1],cnt,0,bound,v,sum);
    }
    int get(int l,int r){
        return query(root[r],l,0,bound);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    mex_segtree tr(n,n);
    for(int i=1;i<=n;i++){
        int ne;cin>>ne;ne=min(ne,n);
        tr.add(ne);
    }
    while(m--){
        int l,r;cin>>l>>r;
        cout<<tr.get(l,r)<<"\n";
    }
    return 0;
}