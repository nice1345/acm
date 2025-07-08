#include <bits/stdc++.h>
#define int long long
struct cmp
{
    bool operator()(std::pair<int, int> q, std::pair<int, int> w)
    {
        return q.second * w.first < q.first * w.second;
    }
};
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> qqq;
    std::vector<std::pair<int, int>> h;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        if (i)
        {
            int g = std::__gcd(a[i], a[i - 1]);
            qqq.push({a[i - 1] / g, a[i] / g});
        }
    }
    while (!qqq.empty())
    {
        auto [x, y] = qqq.top();
        std::cout << "[" << x << ',' << y << "]" << " ";
        h.push_back(qqq.top()), qqq.pop();
    }
    std::cout << '\n';

    if (h.size() == 1)
    {
        std::cout << (*h.begin()).first << '\n';
    }
    else if (h.size() == 2)
    {
        std::cout << (*h.rbegin()).second * (*h.begin()).first / ((*h.rbegin()).first * (*h.begin()).second) << '\n';
    }
    else
    {
        h.erase(h.begin());
        std::cout << (*h.rbegin()).second * (*h.begin()).first / ((*h.rbegin()).first * (*h.begin()).second) << '\n';
    }
}
signed main()
{
    int _ = 1;
    std::cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}