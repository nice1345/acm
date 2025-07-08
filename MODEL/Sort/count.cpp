//计数排序的复杂度为n+w,w为值域
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll mod = (ll) 998244353;
const int N = 100010;
const int W = 100010;

int n, w, tree[N], cnt[W], ans[N];

void counting_sort() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) ++cnt[tree[i]];
    for (int i = 1; i <= w; ++i) cnt[i] += cnt[i - 1];
    //每个a[i]所在的数量前缀和即是它的排名
    for (int i = n; i >= 1; --i) ans[cnt[tree[i]]--] = tree[i];
}

int main() {


    return 0;
}
