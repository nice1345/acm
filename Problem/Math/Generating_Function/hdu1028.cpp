//用母函数求整数划分（hdu 1028）
#include<bits/stdc++.h>
using namespace std;
const int N=200;
int c1[N+1], c2[N+1];
void solve() {
    int i, j, k;
    for(i=0; i<=N; i++){      //初始化，第一部分(1 + x + x2 + ...)的系数，都是1
        c1[i]=1;  c2[i]=0;
    }
    for(k=2; k<=N; k++){      //从第2部分(1 + x2 + x4 + ...)开始展开
        for(i=0; i<=N; i++){//k=2时，i循环第一部分(1+x+x2+...)，j循环第二部分(1+x2+x4+...)
            for(j=0; j+i <= N; j+=k) c2[i+j] += c1[i];
        }
        for(i=0; i <= N; i++) { c1[i] = c2[i];  c2[i] = 0; }  //更新本次展开的结果
    }
}

int dp[N+1][N+1];            //dp[len][m]: 将n划分成最大数不超过m的划分数
void solve1() {                //预计算dp[len][m]，求出所有n的划分
    for(int n=1; n<=N; n++)
        for(int m=1; m<=N; m++){
            if((n==1)||(m==1))   dp[n][m] = 1;
            else if(n < m)       dp[n][m] = dp[n][n];
            else if(n == m)      dp[n][n] = dp[n][n-1]+1;
            else                 dp[n][m] = dp[n-m][m] + dp[n][m-1] ;
            //(len,m)=每个数不超过m-1 加 (至少扫有一个)必有一个m
        }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    solve();
    while(cin >> n)   cout << c1[n] << endl;

//    solve1();
//    while(cin >> len)  cout << dp[len][len] << endl;
    return 0;
}
