#include<bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<int>a(n+1);
    map<int,int>idx,val;int cnt=0;
    for(int i=1;i<=n;++i)cin>>a[i],idx[a[i]]=1;
    for(auto &[i,j]:idx)j=++cnt,val[cnt]=i;
    vector<vector<int>>b(n+1,vector<int>(n+1,0));
    vector<int>tree(n*4,0);
    function<void(int,int,int)>init=[&](int id,int l,int r){
        tree[id]=0;
        if(l==r)return;
        int mid=(l+r)>>1;
        init(id<<1,l,mid);
        init(id<<1|1,mid+1,r);
    };
    function<void(int,int,int,int)>add=[&](int id,int l,int r,int p){
        if(l==r)tree[id]++;
        else{
            int mid=(l+r)>>1;
            if(p<=mid)add(id<<1,l,mid,p);
            else add(id<<1|1,mid+1,r,p);
            tree[id]=tree[id<<1]+tree[id<<1|1];
        }
    };
    function<int(int,int,int,int)>query=[&](int id,int l,int r,int k){
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(k<=tree[id<<1])return query(id<<1,l,mid,k);
        else return query(id<<1|1,mid+1,r,k-tree[id<<1]);
    };
    for(int l=1;l<=n;++l){
        for(int r=l;r<=n;++r){
            add(1,1,cnt,idx[a[r]]);
            b[l][r]=query(1,1,cnt,(r-l+2)>>1);
        }
        init(1,1,cnt);
    }
    auto b1=b;
    int l=1,r=cnt;
    int bound=(n*(n+1))>>1;
    bound=(bound+1)>>1;
    function<bool(int)>check=[&](int x){
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                b1[i][j]=0;
        for(int l=1;l<=n;++l)
            for(int r=1;r<=n;++r)
                if(b[l][r]>x)b1[l][r]=1;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                b1[i][j]=b1[i][j]+b1[i-1][j]+b1[i][j-1]-b1[i-1][j-1];
        int res=0;
        for(int l=1;l<=n;++l)
            for(int r=l;r<=n;++r){
                int len=r-l+1,sum=len*(len+1)/2;
                if(sum-(b1[r][r]-b1[l-1][r])>=(sum+1)/2)res++;
            }
        return res>=bound;
    };
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<val[l]<<"\n";
    return 0;
}