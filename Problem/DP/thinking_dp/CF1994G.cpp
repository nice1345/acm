#include<bits/stdc++.h>
using namespace std;
#define vec vector
#define vi vec<int>
#define vb vec<bool>
#define vc vec<char>
#define vvi vec<vec<int>>
string ne;
/**
 靠，这才是思路的正确打开方式
 dp[i][j]表示前i-1位，留下了j个pow(2,i)
 主要担心j的取值范围
 假设每一个低位都取到极限
 i-1位有n个1(2^i-1)，传到i位还剩n/2个1(2^i)
 i-2位有n个1，传到i位还剩n/4个1
 n+n/2+n/4+n/8+n/16+....=n*(1+1/2+1/4+1/8+1/16+...)
 这玩意能大到哪去
 假设有m项,等比公式得2-2^m-1<2;
 传递到第i位上的1最多不超过2*n
 * */
void solve() {
    int n,k;cin>>n>>k;
    vb s(k,0);
    for(int i=0;i<k;i++){
        char tt;cin>>tt;
        if(tt=='1')s[k-i-1]=1;
    }
    vi a(k,0),b(k,0);
    for(int i=0;i<n;i++){
        cin>>ne;
        for(int j=0;j<k;j++)
            if(ne[j]=='1')a[k-j-1]++;
            else b[k-j-1]++;
    }
    vvi f(k+1,vi(n,-1)),dp(k+1,vi(n,-1));
    f[0][0]=1;
    for(int i=0;i<k;i++)
        for(int j=0;j<n;j++){
            if(f[i][j]==-1)continue;
            if((s[i]&&((j+b[i])&1))||(!s[i]&&(((j+b[i])&1)==0)))
                f[i+1][(j+b[i])>>1]=1,dp[i+1][(j+b[i])>>1]=j;

            if((s[i]&&((j+a[i])&1))||(!s[i]&&(((j+a[i])&1)==0)))
                f[i+1][(j+a[i])>>1]=0,dp[i+1][(j+a[i])>>1]=j;
        }
    if(f[k][0]==-1)cout<<"-1\n";
    else{
        for(int i=k,id=0;i>0;id=dp[i][id],i--)cout<<f[i][id];
        cout<<"\n";
    }
}
/**
 勾史，暴搜加剪枝，出这种题有锤子意义
 * */

void solve1() {

}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

