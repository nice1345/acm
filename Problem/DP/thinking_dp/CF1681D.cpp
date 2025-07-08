#include <bits/stdc++.h>
using namespace std;
int t, n,last,now;

void solve1(){
    // scanf("%d",&len);
    vector<vector<int>>dp(n,vector<int>(2));
    scanf("%d",&last);
    for(int i=1;i<n;i++){
        scanf("%d",&now);
        if(now>last){
            dp[i][0]=min(dp[i-1][0],dp[i-1][1]+1);
            dp[i][1]=dp[i-1][1]+1;
        }
        else if(now<last){
            dp[i][0]=min(dp[i-1][0],dp[i-1][1])+1;
            dp[i][1]=dp[i-1][1];
        }
        else {
            dp[i][0]=min(dp[i-1][0],dp[i-1][1])+1;
            dp[i][1]=dp[i-1][1]+1;
        }
        last=now;
        printf("%d %d %d\n",i,dp[i][0],dp[i][1]);
    }
    printf("%d\n", min(dp[n-1][0],(dp[n-1][1]+1)));
}


int main(){
    scanf("%d",&t);
   for(int i=0;i<t;i++){
       solve1();
   }
    return 0;
}
