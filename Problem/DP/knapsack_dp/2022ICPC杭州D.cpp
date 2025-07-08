#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll mod=(ll)998244353;
ll dp[3005][2],dp1[3005][2];

ll n,p,ne,len,ma=0;


/***
 dp[k][i]
 i为0 刚好装满k容量时且一定没有装入部分的最大收获
 i为1 刚好装满k容量时且一定装入部分的最大收获
 */
void solve(){
    cin>>n>>len;

    for(int i=1;i<=n;i++){
        cin>>p;
        for(int j=1;j<p;j++){
            cin>>ne;
            for(int k=len-j;k>=0;k--)
                if(dp[k][0]||k==0)dp1[k+j][1]= max(dp1[k+j][1],(ne+dp[k][0]));
        }

        cin>>ne;
        for(int k=len-p;k>=0;k--){
            if(dp[k][0]||k==0)
                dp1[k+p][0]= max(dp1[k+p][0],(ne+dp[k][0]));
            if(dp[k][1])dp1[k+p][1]= max(dp1[k+p][1],(ne+dp[k][1]));
        }

        for(int k=len;k;k--){
            dp[k][0]=dp1[k][0];
            dp[k][1]=dp1[k][1];
        }
    }

    ///装入部分时必须装满,没有部分时一定要枚举完所有的容量
    ma=max(dp[len][0],dp[len][1]);
    for(int i=len-1;i;i--){
        ma=max(ma,dp[i][0]);
    }
    cout<<ma<<endl;

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    // cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}




