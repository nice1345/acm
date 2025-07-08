#include <bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=(int)1e5+1;
ll mod=(long)1e9+7;
int t;
int n,s;
ll dp[N];
int open[4],d[4];
int tmp,ov;
ll ans,now;
int main() {
    for(int i=0;i<4;i++)scanf("%d",&open[i]);
    dp[0]=1;
    for(int i=0;i<4;i++){
        for(int j=open[i]; j < N; j++){
            dp[j]+=dp[j - open[i]];
        }
    }
    scanf("%d",&t);
    while (t--){
        for(int i=0;i<4;i++)scanf("%d",&d[i]);
        scanf("%d",&s);
        ans=dp[s];
        for(int i=1;i<=15;i++){
            now=s;tmp=i;ov=0;
            for(int j=0;tmp;j++){
                if(tmp&1)
                    ov^=1,now-= (d[j]+1) * open[j];
                tmp>>=1;
            }
            if(now<0)continue;
            if(ov)ans-=dp[now];
            else ans+=dp[now];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
