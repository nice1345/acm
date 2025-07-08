#include <bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=(int)1e5+1;
ll mod=998244353;
int t;
const int mn=105,mm=2005;
int n,m,tree[mn][mm],sum[mn][mm];
ll f[mn][mn*2],g[mn][mn],ans,ans1;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    //法1算总 类似生成函数
    ans1=1;
    for(int i=1;i<=n;i++){
        for( int j=1;j<=m;j++){
            cin >> tree[i][j];
            sum[i][0]= (sum[i][0] + tree[i][j]) % mod;
        }
        ans1=(ans1*(ll)(sum[i][0]+1))%mod;
    }
ans1=(ans1-(ll)1+mod)%mod;

    for(int i=1;i<=n;i++)
        for( int j=1;j<=m;j++)
            sum[i][j]= (sum[i][0] - tree[i][j] + mod) % mod;
    ans=0;
    //枚举不合法的列
    //f数组第二维开2n是映射-n到n即当前列比其他列多了n或少了n;
    for(int col=1;col<=m;col++){
        memset(f,0,sizeof f);
        f[0][n]=1;
        for(int i=1;i<=n;i++)
            for(int j=n-i;j<=n+i;j++)
                f[i][j]=(f[i-1][j]   //这一行不拿 前i行col列比其他列多了j个
                        + ((j>0) ? (f[i-1][j-1] * tree[i][col] % mod) : 0)//这一行拿col列 前i行col列比其他列多了j-1个(事实证明不处理j=0也行,但不处理这j-1我都不知道为啥数组不越界)
                        +f[i-1][j+1]*sum[i][col]%mod)%mod;//这一行拿其他列 前i行col列比其他列多了j+1个

    //col比其他列多,那col列一定不合法
        for(int j=1;j<=n;j++)
            ans=(ans+f[n][n+j])%mod;

    }
//    //法2算总
//    ans1=0;
//    g[0][0]=1;
//    for(int i=1;i<=len;i++)
//        for(int j=0;j<=len;j++)
//            g[i][j]=(g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%mod:0))%mod;
//    for(int j=1;j<=len;j++){
//        //sum=(sum-g[len][j]+mod)%mod;
//        ans1=(ans1+g[len][j])%mod;
//    }

   // cout<<sum*(mod-1)%mod<<endl;
      cout<<((ans1-ans)%mod+mod)%mod<<endl;

    return 0;
}
