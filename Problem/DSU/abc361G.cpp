#include<bits/stdc++.h>
using namespace std;
#define vec vector
#define order(vv)  sort(vv.begin(),vv.end())
const int N = 2e5;
struct dsu{
    vec<int>fa;
    dsu(int n){
        fa.resize(n+5);
        iota(fa.begin(), fa.end(),0);
    }
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void unite(int x,int y){x=find(x);y=find(y);fa[x]=y;}
};
void solve(){
    int n;cin>>n;
    vec<vec<int>>din(N+3,{-2,N+2});
    for(int i=0;i<n;i++){
        int u,v;cin>>u>>v;
        din[v+1].push_back(u);
    }
    vec<vec<array<int,3>>>seg(N+3,vec<array<int,3>>(0));
    int cnt=0;
    seg[0].push_back({-1,N+1,0});
    dsu ds(N*2);
    auto ch=[&](array<int,3> a,array<int,3> b){
        if(b[1]<a[0])return -1;
        if(a[1]<b[0])return 1;
        return 0;
    };
    for(int d=1;d<=N+2;d++){
        order(din[d]);
        int len=din[d].size();
        int idx=0,id=-1;
        for(int j=0;j<len-1;j++)
            if(din[d][j+1]-din[d][j]>1){
                seg[d].push_back({din[d][j]+1,din[d][j+1]-1,++cnt});id++;
                while(idx<seg[d-1].size()&&ch(seg[d][id],seg[d-1][idx])==-1)idx++;
                while(idx<seg[d-1].size()&&ch(seg[d][id],seg[d-1][idx])==0)
                    ds.unite(cnt,seg[d-1][idx][2]),idx++;
                idx--;
            }
    }
    int o=ds.find(0);
    long long ans=0;
    for(int d=1;d<=N+2;d++)
        for(auto [l,r,i]:seg[d])
            if(ds.find(i)!=o)
                ans+=(long long)(r-l+1);
    cout<<ans<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

