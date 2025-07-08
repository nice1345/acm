#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n,u,v,num=1;
int c[N];
vector<int>g[N],ve[N];
int w[N],sum[N],h[N],r[N];
bool vis[N],hh[N];
ll ans[N],c_sum[N];
void calc(int rt,int len){
    vector<int>vv;
    int rt1=0;
    ll all=0;
    function<void(int,int,int)>dfs=[&](int no,int fa,int ro){
        if(!hh[c[no]]){
            hh[c[no]]= true;
            vv.push_back(c[no]);
        }
        if(!h[c[no]])num++;
        h[c[no]]++;
        ans[rt]+=num;
        ans[no]+=num;
        sum[no]=1;
        for(int so:g[no]){
            if(so==fa||vis[so])continue;
            dfs(so,no,ro);
            sum[no]+=sum[so];
        }
        h[c[no]]--;
        if(!h[c[no]]){
            num--;
           c_sum[c[no]]+=sum[no];
           all+=sum[no];
           ve[ro].push_back(no);
        }
    };
    vv.push_back(c[rt]);
    hh[c[rt]]= true;
    vis[rt]= true;
    h[c[rt]]=1;all=0;
    for(int so:g[rt]){
        if(vis[so])continue;
        ve[so].clear();
        dfs(so,rt,so);
        c_sum[c[rt]]+=sum[so];
        all+=sum[so];
    }
    function<void(int,int,int)>find=[&](int no,int fa,int le){
        if(!h[c[no]])all+=len-1-le-c_sum[c[no]];
        ans[no]+=all;
        h[c[no]]++;
        w[no]=0;
        for(int so:g[no]){
            if(so==fa||vis[so])continue;
            find(so,no,le);
            w[no]=max(w[no],sum[so]);
        }
        w[no]=max(w[no],le-sum[no]);
        if(w[no]<=le/2)rt1=no;
        h[c[no]]--;
        if(!h[c[no]])all-=len-1-le-c_sum[c[no]];
    };
    for(int so:g[rt]){
        if(vis[so])continue;
        all-=sum[so];
        for(int i:ve[so]){
            all-=sum[i];
            c_sum[c[i]]-=sum[i];
        }
        rt1=0;
        find(so,rt,sum[so]);
        all+=sum[so];
        for(int i:ve[so]){
            all+=sum[i];
            c_sum[c[i]]+=sum[i];
        }
        if(sum[so]!=1)r[so]=rt1;
    }
    for(int i:vv){
        hh[i]= false;
        c_sum[i]=0;h[i]=0;
    }
    for(int so:g[rt])
        if (!(vis[so]||sum[so]==1))
        calc(r[so],sum[so]);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<n;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    calc(1,n);
    for(int i=1;i<=n;i++)cout<<ans[i]+(ll)1<<"\n";
    return 0;
}
