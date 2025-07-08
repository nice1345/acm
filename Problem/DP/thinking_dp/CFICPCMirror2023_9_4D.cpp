//https://codeforces.com/contest/1866/problem/D
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int M = 15;
/**
 方案数取得列具有单调性,
 每一列取j个数就取那一列排序后的前缀和
 前面的列的最大值也可以取个前缀和
 * */
//ll tree[M][N],dp[M][N];
ll tree[M][N],f[M][N],dp[M][N];//MAX[M][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //别人写的,枚举列,没看懂
//    memset(dp,0x80,sizeof dp);
//    int len,m,k;
//    cin>>len>>m>>k;
//    for(int i=0;i<len;i++){
//        for(int j=0;j<m;j++){
//            cin>>tree[i][j];
//            if(j==0) {
//                dp[0][0]=max(dp[0][0],tree[i][j]);
//            }
//        }
//    }
//    dp[1][0]=0;
//    for(int i=1;i<m;i++){
//        vector<ll> v;
//        for(int t=0;t<len;t++){
//            v.push_back(tree[t][i]);
//        }
//        sort(v.begin(),v.end(),greater());
//        for(int t=1;t<len;t++){
//            v[t]+=v[t-1];
//        }
//
//        for(int j=max(0,i+k-m);j<=min(k-1,i+1);j++){
//
//            for(int j2=max(max(0,i-1+k-m),j-1);j2<=min(len-1+j,min(k-1,i));j2++){
//
//                int cnt=1+j2-j;
//
//                dp[j][i]=max(dp[j][i], dp[j2][i-1]+(cnt>0?v[cnt-1]:0));
//            }
//        }
//    }
//    cout<<dp[k-1][m-1]<<endl;



//自己写的,根据列的单调性枚举第op个操作取第几列的情况
//[i][op]表示当前第op次操作,取第i列的最大值
    ll ma;
    int n,m,k;cin>>n>>m>>k;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> tree[i][j];
    vector<ll>v(n+1);
    //每一列算最大值前缀和
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)v[j]=tree[j][i];
        sort(v.begin()+1,v.end());
        for(int j=1;j<=n;j++){
            f[j][i]=v[(n-j+1)];
            f[j][i]+=f[j-1][i];
        }
    }
for(int op=1;op<=(m-k+1);op++){
    //空间有限,每个操作只能取k列,做个映射即可
    for(int i=1;i<=k;i++){
       int no=i+op-1;//当前列
       //这一列取得第j个数,取得第一个数位于[i+j-1][op-j+1],(映射后的)
       //上一个操作编号是op-j,(MAX[i+j-1][op-j])是[1][op-j]到[i+j-1][op-j]的最大值
       //进一步优化空间,[i][op]表示当前第op次操作,取前i列中一列的最大值(最优情况)
       for(int j=1;j<=n&&(op-j)>=0&&((i+j-1)<=k);j++){
//           dp[i][op]= max(dp[i][op],(MAX[i+j-1][op-j]+f[j][no]));
           dp[i][op]= max(dp[i][op],(dp[i+j-1][op-j]+f[j][no]));
       }
    }
    ll ma=0;
    for(int i=2;i<=k;i++){
        dp[i][op]=max(dp[i-1][op],dp[i][op]);
       // ma=max(ma,dp[i][op]);
       // MAX[i][op]=ma;
    }
}
ma=-1;
for(int i=1;i<=k;i++)ma=max(ma,dp[i][m-k+1]);
cout<<ma<<endl;




    return 0;
}