#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define vec vector
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;m=n-m;
    vec<basic_string<int>>g(n+1,basic_string<int>());
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u]+=v;g[v]+=u;
    }
    if(m==2){cout<<"1";return 0;}
    vec<int>deep(n+1);
    int ans=n;
    for(int root=1;root<=n;root++){
        if(g[root].length()==1)continue;
        vec<int>sum(n+1,0);
        function<void(int,int,int)>get_deep=[&](int no,int fa,int de){
            deep[no]=de;sum[de]++;
            for(int so:g[no]){
                if(so==fa)continue;
                get_deep(so,no,de+1);
            }
        };
        get_deep(root,0,0);
        int md=0,res=0;
        for(int d=1;d<n;d++){
            sum[d]+=sum[d-1];
            if(sum[d]>=m){md=d;break;}
        }
        res=md;
        if(md==1){
            ans=min(ans,2);
            continue;
        }
        int k=m-sum[md-1];
        bool flag=0;
        for(int j:g[root]){
            int h=0;
            function<void(int,int,int)>dfs=[&](int no,int fa,int de){
                if(de==md){h++;return;}
                for(int so:g[no]){
                    if(so==fa)continue;
                    dfs(so,no,de+1);
                }
            };
            dfs(j,root,1);
            if(h>=k){
                flag=1;
                break;
            }
        }
        if(flag)res=max(res,md*2-1);
        else res=max(res,md*2);
        ans=min(ans,res);
    }
    cout<<ans;
    return 0;
}

