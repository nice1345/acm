#include <bits/stdc++.h>
using namespace std;
#define m_p make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define fi first
#define se second
typedef long long ll;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnf(2106);
const int N = 200005;
/**
 转移两次就只剩下连续的区间，然后就可以用公式求解
 * */
int n;
int a[N];
bool c[N];
void doit()
{
    for (int i = 1; i <= n; ++i)
        c[i] = false;
    int maxu = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (c[a[i]])
            maxu = max(maxu, a[i]);
        c[a[i]] = true;
        a[i] = maxu;
    }
}
void solv()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += a[i];
    doit();
    for (int i = 1; i <= n; ++i)
        ans += a[i];
    doit();

    for (int i = 1; i <= n; ++i)
        ans += (n - i + 1) * 1LL * a[i];
    cout << ans << "\n";
}

int main()
{

    int tt = 1;
    cin >> tt;
    while (tt--)
    {
        solv();
    }
    return 0;
}