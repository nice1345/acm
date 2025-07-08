//题目链接：https://codeforces.com/contest/1969/problem/C
//题解：https://zhuanlan.zhihu.com/p/695354439
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
//累加，简洁明了的实现方法
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    const LL INF = 1e18;
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<int> v(n + 1);
        for(int i = 1; i <= n; i++) cin >> v[i];
        vector<vector<LL> > dp(n + 1, vector<LL>(k + 1, INF));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            /**
             a:以i为中心往左修改的个数
             sum:以i为中心往左修改的个数
             c:左边界前一位的修改状态,以i为中心修改了a+b次,那么前i-a-1位最多修改c次,把1到c次的状态都转移一下
             * */
            for(int a = 0; a <= min(i - 1, k); a++){
                for(int b = 0; b <= n - i && a + b <= k; b++){
                    for(int c = 0;c<=k-a-b; c++){
                        dp[i + b][a + b + c] = min(dp[i + b][a + b + c], dp[i - a - 1][c] + 1LL * (a + b + 1) * v[i]);
                    }
                }
            }
        }
        cout << *min_element(dp[n].begin(), dp[n].end()) << '\n';
    }

}
