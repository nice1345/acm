#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 100000

int i,j,k,n,m,t,fa[N+50],sz[N+50],vis[N+50];
ll res[N+50];

int find(int x){return (fa[x]==x?x:fa[x]=find(fa[x]));}
vector<pair<int,int> > v;
vector<tuple<int,int,int,int> > q;
unordered_map<int,int> mp;

void hb(int x,int y){
    x=find(x); y=find(y);
    if(--mp[sz[x]]==0)mp.erase(sz[x]);
    if(--mp[sz[y]]==0)mp.erase(sz[y]);
    if(sz[x]>sz[y])swap(sz[x],sz[y]);
    sz[x]+=sz[y]; fa[y]=x; mp[sz[x]]++;
}

void add(int x){
    mp[1]++; sz[x]=1; vis[x]=1;
    if(vis[x-1])hb(x-1,x);
    if(vis[x+1])hb(x,x+1);
}

ll get(int w0,int l,int r){
    ll res=0;
    for(auto [w,num]:mp)if(l<=w){
            ll k=w-l+1; res+=(k*k+k)/2*num;
            k=max(0,w-r); res-=(k*k+k)/2*num;
        }
    return res;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    for(i=1;i<=N;i++)fa[i]=i;
    cin>>n;
    for(i=1;i<=n;i++){cin>>k; v.push_back({k,i});}
    cin>>t;
    sort(v.begin(),v.end());
    for(i=1;i<=t;i++){
        int w,l,r;
        cin>>w>>l>>r;
        q.push_back({w,l,r,i});
    }
    sort(q.rbegin(),q.rend());
    for(auto [w,l,r,id]:q){
        while(!v.empty()){
            auto [x,y]=v.back();
            if(x<w)break;
            add(y); v.pop_back();
        }
        res[id]=get(w,l,r);
    }
    for(i=1;i<=t;i++)cout<<res[i]<<'\n';
}