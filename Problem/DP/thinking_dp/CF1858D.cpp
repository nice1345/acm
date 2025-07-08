//题目链接:https://www.luogu.com.cn/problem/CF1858D
//博客:https://www.cnblogs.com/No-play-Yes-splay/p/codeforces-round-893-div2-sol.html
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = (ll) 998244353;
const int N=3005;
int n,k,pre[N][N],//pre[i][j]记为前i个字符,最多修改j次,所能得到的最长连续的0的数量。
        suf[N][N],//suf[i][j]从i到n,最多修改j次,所能得到的最长连续的0的数量。
ans[N];
string st;

void solve(){
    cin>>n>>k>>st;st="$"+st;
    //先求出以i结尾且最多修改j次的最长连续的0的数量。
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            if(st[i]=='1'){
                if(j)pre[i][j]=pre[i-1][j-1]+1;
                else pre[i][j]=0;
            }
            else pre[i][j]=pre[i-1][j]+1;
        }
    }
//求前i个字符,最多修改j次,所能得到的最长连续的0的数量。
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            pre[i][j]=max({pre[i][j],pre[i-1][j],(j?pre[i][j-1]:0)});
        }
    }
//先求出以i开始最多修改j次的最长连续的0的数量。
    for(int i=n;i;i--){
        for(int j=0;j<=k;j++){
            if(st[i]=='1'){
                if(j)suf[i][j]=suf[i+1][j-1]+1;
                else suf[i][j]=0;
            }
            else suf[i][j]=suf[i+1][j]+1;
        }
    }
//求出从i到n最多修改j次的最长连续的0的数量。
    for(int i=n;i;i--)
        for(int j=0;j<=k;j++)
            suf[i][j]=max({suf[i][j],suf[i+1][j],(j?suf[i][j-1]:0)});
    //枚举长度为i(将里面0全改为1)的区间   本题应该也可以反过来做枚举长度为i(将里面1全改为0)的区间
    for(int i=0;i<=n;i++){
        int d=-1,c=k;
        //求出第一个长度为i的区间有多少个0,对应需要多少次修改
        for(int j=1;j<i;j++)if(st[j]=='0')c--;
        for(int j=1;j<=n-i+1;j++){
            //区间右移一格,只会将区间第一个元素去掉,在末尾增加一个元素
            //所以,维护区间0的数量,只需根据这两个值O(1)维护即可
            if(st[j-1]=='0')c++;
            if(st[j+i-1]=='0')c--;
            //不可能情况
            if(c<0)continue;
            //剩下的连续0只会出现在当前区间的两边的最大值
            d=max({d,pre[j-1][c],suf[j+i][c]});
        }
        //更新答案
        if(~d)for(int j=1;j<=n;j++)ans[j]=max(ans[j],d*j+i);
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<"\n";
    for(int i=0;i<=n;i++){
        ans[i]=0;
        for(int j=0;j<=n;j++){
            pre[i][j]=0;
            suf[i][j]=0;
        }
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while (T--){
        solve();
    }
    return 0;
}
