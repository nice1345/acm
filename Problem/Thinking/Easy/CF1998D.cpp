#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define vec vector
#define vi vec<int>
#define gg(nn) vec<basic_string<int>>g(nn+1,basic_string<int>());
int n,m,cnt;
/**
 题解：https://www.cnblogs.com/luckyblock/p/18353021
 先求每个点的最短路径的时间，
 (重点)
 根据每条特殊边来差分
 * */
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        cin>>n>>m;
        gg(n-1) vec<pii>h(m);
        for(int i=0;i<n-1;i++)g[i]+=i+1;
        for(int i=0;i<m;i++){
            cin>>h[i].first>>h[i].second;
            h[i].first--;h[i].second--;
            g[h[i].first]+=h[i].second;
        }
        vi f(n),d(n + 5);
        for(int i=0;i<n;i++)
            for(int to:g[i])
                if(!f[to] || f[to] > f[i])
                    f[to]= f[i] + 1;
        for(auto [st,to]:h)
            if(st< to - f[st] - 2)
                d[st+1]++,d[to - f[st] - 1]--;
        cnt=0;
        for(int i=0;i<n-1;i++){
            cnt+=d[i];
            if(cnt)cout<<'0';
            else cout<<'1';
        }
        cout<<"\n";
    }
    return 0;
}