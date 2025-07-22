#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int N = 2e5 + 5;
const int mod = 998244353;

/**
 二维坐标系的曼哈顿有特殊性
 先考虑一维，排个序，第一和最后匹配
 但是发现只要前半部分和后半部分任何一位匹配都行


 所以先x排序
 然后前半部分，后半部分对y排序
 整体来看，会有一部分大于前半部分的y会出现在前半部分，
 排完序后，会出现在前半部分尾部，
 会有一部分小于后半部分的y会出现在后半部分，
 排完序后，会出现在后半部分前部，
 两两匹配一样最优

 1234
 1324
 一样最优
 * **/
void solve() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
        return x[i] < x[j];
    });
    sort(order.begin(), order.begin() + n / 2, [&](int i, int j) {
        return y[i] < y[j];
    });
    sort(order.begin() + n / 2, order.end(), [&](int i, int j) {
        return y[i] < y[j];
    });
    for (int i = 0; i < n / 2; i++) {
        cout << order[i] + 1 << " " << order[n - 1 - i] + 1 << '\n';
    }
}

signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int _ = 1;
    std::cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
