#include <bits/stdc++.h>
#define pii pair<int,int>
#define pil pair<int,long long>
#define pli pair<long long,int>
#define vec vector
#define vii vector<int>
#define vll vector<long long>
using namespace std;
typedef long long ll;
char buf[1<<20],*p1,*p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
inline void readT(int &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
inline void writeT(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) writeT(x/10);
    putchar(x%10+'0');return;
}
//#define int long long
ll mod=(ll)998244353;
const int N = 1e5 + 10;
int n;
int dp[1000010];

int f(int a){
    int res=0;
    while (a>0){
        res=max(res,a%10);
        a/=10;
    }
    return res;
}

void solve(){
dp[0]=0;
dp[1]=dp[2]=dp[3]=dp[4]=dp[5]=dp[6]=dp[7]=dp[8]=dp[9]=1;
for(int i=1;i<=1000000;i++){
    for(int j=1;j<=9;j++){
        if(j==f(i+j)){
            if(dp[i+j]==0)dp[i+j]=dp[i]+1;
            else dp[i+j]=min(dp[i]+1,dp[i+j]);
        }
    }
}
cin>>n;
cout<<dp[n]<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    while (T--)solve();



    return 0;
}
