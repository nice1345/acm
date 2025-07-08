#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct BIT{
    int len;
    vector<T>tree;
    BIT(int n){
        tree.resize(n);
        len=n;
    }
    void add(int i,T v){for(;i<len;i+=i&-i)tree[i]+=v;}
    T get(int i){T res=0;for(;i;i-=i&-i)res+=tree[i];return res;}
};
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    while(_--){
        int n,m;cin>>n>>m;
        map<int,int>mp,last;
        map<int,vector<int>>h;
        set<int>qc;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++){
            cin>>a[i];
            h[a[i]].emplace_back(i);
            qc.insert(a[i]);
        }
        int l1=0,mex=1;for(int i:qc){last[i]=l1+1;l1=i;if(mex==i)mex++;}
        vector<array<int,3>>seg;
        for(auto [id,b]:h){
            if(id>n)continue;
            if(b[0]>1)seg.push_back({1,b[0]-1,last[id]});
            for(int i=0;i<(int)b.size()-1;++i)
                if(b[i+1]>b[i]+1)
                    seg.push_back({b[i]+1,b[i+1]-1,last[id]});
            if(b[(int)b.size()-1]<n)seg.push_back({b[(int)b.size()-1]+1,n,last[id]});
        }
        sort(seg.begin(),seg.end(),[&](array<int,3> a,array<int,3> b){
            return a[1]<b[1];
        });
        BIT<int> tree(n+5);
        int st=0;
        int ans=(int)qc.size()-mex;
        for(auto [l,r,v]:seg){
            while(st<r){
                ++st;
                int cur=a[st];
                if(mp.count(cur))tree.add(mp[cur], -1);
                mp[cur]=st;
                tree.add(st,1);
            }
            ans=max(ans,tree.get(r)-tree.get(l-1)-v);
        }
        cout<<ans<<"\n";
    }
    return 0;
}