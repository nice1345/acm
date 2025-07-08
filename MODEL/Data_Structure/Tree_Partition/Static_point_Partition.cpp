#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N= 10005;
const int inf=2e9;
vector<pair<int,int>>g[N];
int n,m,u,v,w;
int tree[100];
bool vis[N],h[100];
int len,rt,id,son_num[N],weight[N];
void get_sum(int no,int fa){
    len++;
    for(auto[so,wi]:g[no])
        if(!vis[so]&&so!=fa)get_sum(so,no);
}
void get_rt(int no,int fa){
    weight[no]=0;
    son_num[no]=1;
    for(auto[so,wi]:g[no]){
        if(vis[so]||so==fa)continue;
        get_rt(so,no);
        if(rt!=0)return;
        son_num[no]+=son_num[so];
        weight[no]=max(weight[no],son_num[so]);
    }
    weight[no]= max(weight[no],len-son_num[no]);
    if(weight[no]<=len/2)rt=no;
}
void cal(int no){
len=0;
get_sum(no,0);
if(len==1)return;
rt=0;
get_rt(no,0);
vector<unordered_map<int,int>> di(g[rt].size());
unordered_map<int,int>qc;
function<void(int,int,int)> get_dis=[&](int no,int dis,int fa){
    di[id][dis]++;
    qc[dis]++;
    for(auto[so,wi]:g[no])
        if (!vis[so]&&so!=fa)get_dis(so,dis+wi,no);
};
int l=0;
for(id=0;id<g[rt].size();id++)
    if(!vis[g[rt][id].first]){
        l++;
        get_dis(g[rt][id].first,g[rt][id].second,rt);
    }
for(int i=0;i<m;i++)if(!h[i]&&qc[tree[i]])h[i]= true;
if(l>1) {
    for (id = 0; id < g[rt].size(); id++) {
        if (vis[g[rt][id].first])continue;
        for (auto[i, j]: di[id])qc[i] -= j;
        for (auto[i, j]: di[id])
            for (int k = 0; k < m; k++)
                if (!h[k] && tree[k] > i && qc[tree[k] - i])
                    h[k] = true;
        for (auto[i, j]: di[id])qc[i] += j;
    }
}
vis[rt]= true;
for(auto[i,j]:g[rt])if(!vis[i])cal(i);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
cin>>n>>m;
for(int i=1;i<n;i++){
    cin>>u>>v>>w;
    g[u].push_back({v,w});
    g[v].push_back({u,w});
}
for(int i=0;i<m;i++)cin >> tree[i];
cal(1);
for(int i=0;i<m;i++)
    if(h[i])cout<<"AYE\n";
    else cout<<"NAY\n";
    return 0;
}

