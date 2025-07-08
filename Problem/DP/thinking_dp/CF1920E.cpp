#include <bits/stdc++.h>
#define For(i,a,b) for(ll i=(a);i<=(b);++i)
#define Rep(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
//#define int long long
char buf[1<<20],*p1,*p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
inline void read(int &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');return;
}
const int N = 2505;
const int mod = 998244353;
int n,k;
int ans;
int dp[N][N];
void solve() {
cin>>n>>k;
ans=0;
//vector<vector<int>>dp(len+5,vector<int>(k+5));
for(int i=0;i<k;i++)dp[0][i]=1;
for(int i=0;i<n;i++)
    for(int j=0;j<k;j++){
        // if(dp[i][j])
        for(int t=0;t+j<k&&(t+1)*(j+1)+i<=n;t++)
            dp[(t+1)*(j+1)+i][t]+=dp[i][j],
                    dp[(t+1)*(j+1)+i][t]%=mod;
        dp[i][j]=0;
    }
for(int i=0;i<k;i++)ans=(ans+dp[n][i])%mod,dp[n][i]=0;
cout<<ans<<"\n";
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }
    return 0;
}
