//题目：https://ac.nowcoder.com/acm/contest/75768/D
//题解：https://blog.nowcoder.net/n/530f0e770557474f8aa001583f2857a8

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 1000000005
#define Yes cout<<"Yes"<<"\n"
#define No cout<<"No"<<"\n"
#define Pair pair<int,int>
#define pqg(u) priority_queue<u,vector<u>,greater<u>>
//小根堆
#define pq(u) priority_queue<u>
//大根堆
#define st first
#define value second
//#define mol %= (int)1e9+7
/*bool cmp(int a,int b){
    return a>b;
}*/
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    vector<vector<Pair>> edge(n+1);
    int sum=0;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        edge[max(x,y)].emplace_back(min(x,y),w);
        sum+=w;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            dp[i][i+len-1]=max(dp[i][i+len-1],dp[i][i+len-2]);

            for(auto e:edge[i+len-1]){
                if(e.st<i) continue;
                int temp=e.value;
                if(i<e.st-1){
                    temp+=dp[i][e.st-1];
                }
                if(e.st+1<i+len-2){
                    temp+=dp[e.st+1][i+len-2];
                }
                dp[i][i+len-1]=max(dp[i][i+len-1],temp);
            }
            /*for(int k=i;k<i+len-1;k++){
                dp[i][i+len-1]=max(dp[i][i+len-1],dp[i][k]+dp[k+1][i+len-1]);
                if(edge[k][i+len-1]!=inf){
                    int temp=edge[k][i+len-1];
                    if(i<=k-1){
                        temp+=dp[i][k-1];
                    }
                    if(k+1<=i+len-2){
                        temp+=dp[k+1][i+len-2];
                    }
                        dp[i][i+len-1]=max(dp[i][i+len-1],temp);
                }
            }*/
        }
    }

    cout<<sum-dp[1][n]<<"\n";
}
int32_t main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t=1;
    //int t; cin>>t;

    while(t--){
        solve();
    }
    return 0;
}