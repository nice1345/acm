#include<bits/stdc++.h>
using namespace std;
#define int long long
//题解：https://www.cnblogs.com/luckyblock/p/18304357#e
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    while(_--){
        int n;cin>>n;
        vector<int> ls(n + 1),rs(n + 1),st(n + 1),a(n + 1),b(n+1),lsi(n + 1, 1),rsi(n + 1, 1);
        int ans=0,k=0,root;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            bool flag=0;
            while(k>0&&a[i]<a[st[k]])k--,flag=1;
            if(k)rs[st[k]]=i;
            if(flag)ls[i]=st[k + 1];
            st[++k]=i;
        }
        root=st[1];
        function<int(int)>get_si=[&](int cur){
            if(ls[cur])lsi[cur]+=get_si(ls[cur]);
            if(rs[cur])rsi[cur]+=get_si(rs[cur]);
            ans+=lsi[cur]*rsi[cur]*a[cur];
            return lsi[cur]+rsi[cur]-1;
        };
        get_si(root);
        function<void(int,int,int)>dfs=[&](int cur,int lch,int rch){
            b[cur]=lch+rch-lsi[cur]*rsi[cur]*a[cur];
            vector<int>lc,rc;
            int s=ls[cur];
            while(s)lc.emplace_back(s),s=rs[s];
            s=rs[cur];
            while(s)rc.emplace_back(s),s=ls[s];
            s=0;
            for(int i:lc){
                while(s<rc.size()&&a[rc[s]]<a[i])s++;
                if(s<rc.size())b[cur]+=lsi[i]*(lsi[rc[s]]+rsi[rc[s]]-1ll)*a[i];
            }
            s=0;
            for(int i:rc){
                while(s<lc.size()&&a[lc[s]]<a[i])s++;
                if(s<lc.size())b[cur]+=rsi[i]*(lsi[lc[s]]+rsi[lc[s]]-1ll)*a[i];
            }
            if(ls[cur])dfs(ls[cur],lch-rsi[cur]*a[cur],rch);
            if(rs[cur])dfs(rs[cur],lch,rch-lsi[cur]*a[cur]);
        };
        dfs(root,0,0);
        for(int i=1;i<=n;i++)cout<<ans+b[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
