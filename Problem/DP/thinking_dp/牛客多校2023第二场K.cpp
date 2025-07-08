//三种状态:0左移一格,1不动,2右移一格
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
long long f[N + 5][3], a[N + 5];
int pos[N + 5], cnt, b[N + 5];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
        if (b[i])
            pos[++cnt] = i;
    }
    if (!cnt){
        printf("0");
        return 0;
    }
    memset(f, 0xcf, sizeof(f)); // 初始化为全-inf
    f[1][1] = a[pos[1]];
    if (pos[1] > 1)
        f[1][0] = a[pos[1] - 1];
    if (pos[1] < n)
        f[1][2] = a[pos[1] + 1];
    for (int i = 2; i <= cnt; i++)
        for (int j = 0; j <= 2; j++)
            for (int k = 0; k <= 2; k++)
                // 不越界，盖子之间相对位置关系保持(避免盖子盖到同一个物体上)
                if (pos[i - 1] + k - 1 < pos[i] + j - 1 && pos[i] + j - 1 <= n)
                    f[i][j] = max(f[i][j], f[i - 1][k] + a[pos[i] + j - 1]);
    printf("%lld", max({f[cnt][0], f[cnt][1], f[cnt][2]}));
    return 0;
}
