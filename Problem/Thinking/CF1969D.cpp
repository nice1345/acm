//题目链接：https://codeforces.com/contest/1969/problem/D
//题解：https://zhuanlan.zhihu.com/p/696549146
/**
 根据利润公式，Bob会选择bi最大的k个
 按照按bi从小到大排个序
 利用优先队列从右往左求出i+1~n里最小的k个a[i]
 从左往右扫描可以求出1~i里面所有的bi>ai的(bi-ai)的和
 枚举断点，1~i里面所有的bi>ai的(bi-ai)的和为利润，i+1~n里最小的k个a[i]纯亏本
 利润-纯亏本==最终利润
 sum=max(max(最终利润),0)
  */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n), b(n);
        for (int &i:a)cin>>i;
        for (int &i:b)cin>>i;
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(),
                  [&](int i, int j) {
                      return b[i] < b[j];
                  });

        ll ans = 0;
        std::vector<ll> profit(n + 1);
        for (int i = 0; i < n; i++)
            profit[i + 1] = profit[i] + std::max(b[p[i]] - a[p[i]], 0);
        ll sum = 0;
        std::priority_queue<int> pq;
        for (int i = n; i >= 0; i--) {
            if (i < n) {
                pq.push(a[p[i]]);
                sum += a[p[i]];
            }
            while (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            if (pq.size() == k) {
                ans = std::max(ans, profit[i] - sum);
            }
        }
        std::cout << ans << "\n";
    }
    return 0;
}
