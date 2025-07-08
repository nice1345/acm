#include<bits/stdc++.h>
using namespace std;
struct node{int ls=0,rs=0,mi=0;};
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    vector<node>tree(n*20+70);
    vector<int>root(n+1);
    int cnt=0;
    function<int(int,int)>build=[&](int l,int r){
        int id=++cnt;
        if(l==r)return id;
        int mid=(l+r)>>1;
        tree[id].ls=build(l,mid);
        tree[id].rs=build(mid+1,r);
        return id;
    };
    function<void(int,int,int,int,int,int)>update=[&](int nr,int cr,int l,int r,int loc,int v){
        tree[cr]=tree[nr];
        if(l==r){tree[cr].mi=v;return;}
        int mid=(l+r)>>1;
        if(loc<=mid){tree[cr].ls=++cnt;update(tree[nr].ls,cnt,l,mid,loc,v);}
        else{tree[cr].rs=++cnt;update(tree[nr].rs,cnt,mid+1,r,loc,v);}
        tree[cr].mi=min(tree[tree[cr].ls].mi,tree[tree[cr].rs].mi);
    };
    function<int(int,int,int,int)>query=[&](int cur,int last,int l,int r){
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(tree[tree[cur].ls].mi<last)return query(tree[cur].ls,last,l,mid);
        else return query(tree[cur].rs,last,mid+1,r);
    };
    root[0]=build(0,n);
    for(int i=1;i<=n;i++){
        int ne;cin>>ne;ne=min(ne,n);
        root[i]=++cnt;
        update(root[i-1],cnt,0,n,ne,i);
    }
    while(m--){
        int l,r;cin>>l>>r;
        cout<<query(root[r],l,0,n)<<"\n";
    }
    return 0;
}