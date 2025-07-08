#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+1;
const int mod =1e9+7;
int cnt=0;
vector<int>primes;
int val[N];
int dp[N][21];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    val[1]=1;
    for(int i=2;i<N;i++){
        if(!val[i]){
            primes.emplace_back(i);
            cnt++;
            val[i]=i;
        }
        for(int j=0;j<cnt&&primes[j]<=1000000/i;j++){
            val[primes[j] * i]=primes[j];
            if(i%primes[j]==0)break;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<21;i++)dp[0][i]=2;
    for(int i=1;i<N;i++){
        dp[i][0]=1;
        for(int j=1;j<21;j++)
            dp[i][j]=(dp[i][j-1]+dp[i-1][j])%mod;
    }
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        int n,r;cin>>r>>n;
        long long ans=1;
        while(n>1){
            int p=val[n],k=0;
            while(val[n]==p){k++;n/=p;}
            ans=ans*(long long)dp[r][k]%(long long)mod;
        }
        cout<<ans<<"\n";
    }
    return 0;
}