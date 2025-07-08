#include<bits/stdc++.h>
using namespace std;
const int mod =1e9+7;
signed main(){
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        vector<int>a(n+1,0),b(m+1,0);
        vector<long long>arr(n+1,0);
        for(int i=1;i<=n;++i){
            cin>>a[i];
            arr[i]=(long long)a[i]+arr[i-1];
        }
        for(int i=1;i<=m;++i)cin>>b[i];
        vector<map<int,int>>mp(m+1),hh(m+1);
        map<pair<int,int>,vector<pair<int,int>>>del;
        vector<vector<pair<int,int>>>f(n+1,vector<pair<int,int>>(m+1,{-1,-1}));
        function<int(int,int)>calc=[&](int val,int st){
            if(st==n||a[st+1]>val)return 0;
            int l=st+1,r=n;
            while(l<r){
                int mid=(l+r+1)>>1;
                if(arr[mid]-arr[st]<=val)l=mid;
                else r=mid-1;
            }
            return l;
        };
        for(int i=0;i<=m;i++)f[0][i]={0,1};
        for(int i=0;i<=n;i++){
            int cur=INT_MAX,cost=-1,last;
            for(int j=1;j<=m;j++){
                if(mp[j].size()>0)f[i][j]=*mp[j].begin();
                if(f[i][j].first!=-1){
                    if(cur>f[i][j].first){
                        cur=f[i][j].first;
                        cost=f[i][j].second;
                    }
                    else if(cur==f[i][j].first)cost=(cost+f[i][j].second)%mod;
                }
                if(cost==-1){
                    for(auto [o,p]:del[{i,j}]){
                        mp[j][o]=(mp[j][o]+mod-p)%mod;
                        hh[j][o]--;
                        if(hh[j][o]==0)mp[j].erase(o);
                    }
                    continue;
                }
                if(i==0)cost=1;
                last=calc(b[j],i);
                if(last==0){
                    for(auto [o,p]:del[{i,j}]){
                        mp[j][o]=(mp[j][o]+mod-p)%mod;
                        hh[j][o]--;
                        if(hh[j][o]==0)mp[j].erase(o);
                    }
                    continue;
                }
                mp[j][cur-j+m]=(mp[j][cur-j+m]+cost)%mod;
                hh[j][cur-j+m]++;
                del[{last,j}].emplace_back(cur-j+m,cost);
                for(auto [o,p]:del[{i,j}]){
                    mp[j][o]=(mp[j][o]+mod-p)%mod;
                    hh[j][o]--;
                    if(hh[j][o]==0)mp[j].erase(o);
                }
            }
        }
        map<int,int>ans;
        for(int i=1;i<=m;i++)
            if(f[n][i].first!=-1)
                ans[f[n][i].first]=(ans[f[n][i].first]+f[n][i].second)%mod;
        if(ans.size()==0)cout<<"-1\n";
        else
            cout<<ans.begin()->first<<" "<<ans.begin()->second<<"\n";
    }
    return 0;
}