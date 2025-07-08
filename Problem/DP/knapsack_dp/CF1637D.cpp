#include <bits/stdc++.h>
using namespace std;
//化简式子,求出所有可能的值
int T, n, tree[105], ans[105];

int main(){
    scanf("%d", &T);
    while(T--) {
        int minSum = 0, maxSum = 0, rSum = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &tree[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &ans[i]);
        for(int i = 1; i <= n; ++i) {
            if(tree[i] > ans[i]) swap(tree[i], ans[i]);
            minSum += tree[i];
            maxSum += ans[i];
            rSum += tree[i] * tree[i] + ans[i] * ans[i];
        }
        bitset<105 * 105> dp;
        dp[0] = 1;
        for(int i = 1; i <= n; ++i)
            dp |= dp << (ans[i] - tree[i]);//不取的可能加上取的可能
        int ans = maxSum * maxSum + minSum * minSum;
        for(int i = 0; i < maxSum - minSum; ++i)
            if(dp[i])//当前值是否可能
                ans = min(ans, (maxSum - i) * (maxSum - i) + (minSum + i) * (minSum + i));
        printf("%d\n", (n - 2) * rSum + ans);

    }
    return 0;
}
