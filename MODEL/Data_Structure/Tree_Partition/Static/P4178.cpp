#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/**
给定一棵 n个节点的树，每条边有边权，求出树上两点距离小于等于k的点对数量。

第一行两个数n, m。
第2到第n行,每行三个整数u,v,w,代表树上存在一条连接u和v边权为w的路径。
接下来n+1行，一个整数k。
 * */
const int N= 40005;
vector<pair<int,int>>g[N];
int n,k,u,v,w,ans=0,pw=0;
bool vis[N];
int len,rt,id,l,r,son_num[N],weight[N];
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
    vector<vector<int>> di(g[rt].size());
    vector<int>qc;
    function<void(int,int,int)> get_dis=[&](int no,int dis,int fa){
        di[id].push_back(dis);
        qc.push_back(dis);
        for(auto[so,wi]:g[no])
            if (!vis[so]&&so!=fa)get_dis(so,dis+wi,no);
    };
    for(id=0;id<g[rt].size();id++)
        if(!vis[g[rt][id].first]){
            get_dis(g[rt][id].first,g[rt][id].second,rt);
            sort(di[id].begin(),di[id].end());
        }
    sort(qc.begin(),qc.end());
    l=0;r=(int)qc.size()-1;
    while (r>=0){
        if(qc[r]<=k)pw++;
        //l<r避免重复,也可以不保证这一条件,输出时ans/2
        while (l+1<qc.size()&&l+1<r&&qc[l+1]+qc[r]<=k)l++;
        if(l==r)l--;
        if(l>=0&&qc[l]+qc[r]<=k)ans+=l+1;
        r--;
    }
    for (id = 0; id < g[rt].size(); id++){
        if (vis[g[rt][id].first])continue;
        l=0;r=(int)di[id].size()-1;
        while (r>=0){
            //l<r避免重复,也可以不保证这一条件,输出时ans/2
            while (l+1<di[id].size()&&l+1<r&&di[id][l+1]+di[id][r]<=k)l++;
            if(l==r)l--;
            if(l>=0&&di[id][l]+di[id][r]<=k)ans-=l+1;
            r--;
        }
    }
    vis[rt]= true;
    for(auto[i,j]:g[rt])if(!vis[i])cal(i);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    cin>>k;
    cal(1);
    cout<<ans+pw;
    return 0;
}

