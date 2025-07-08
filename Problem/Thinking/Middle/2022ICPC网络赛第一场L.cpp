#include<bits/stdc++.h>
using namespace std;
//题解：https://zhuanlan.zhihu.com/p/565553750
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string s,t;cin>>s>>t;
    vector<set<int>>hh(26);
    for(int i=0;i<26;i++)
        for(int j=0;j<26;j++)
            hh[i].insert(j);
    set<int>vis;
    for(int i=1;i<=t.size();i++){
        int cur=t[i-1]-'a';
        for(int j:vis)
            hh[cur].erase(j);
        vis.insert(cur);
    }
    vector<vector<int>>h(26);
    for(int i=0;i<26;i++)
        for(int j:hh[i])
            h[i].emplace_back(j);
    int ans=0;
    vector<int>a={};
    for(char i:s){
        if(vis.count(i-'a'))a.emplace_back(i-'a');
        else ans++;
    }
    vector<int>dp(26,0);
    int ma=0;
    for(int i=0;i<a.size();i++){
        int cur=1;
        for(int ne:h[a[i]])
            cur=max(cur,dp[ne]+1);
        ma=max(ma,cur);
        dp[a[i]]=max(dp[a[i]],cur);
    }
    cout<<ma+ans<<"\n";
    return 0;
}