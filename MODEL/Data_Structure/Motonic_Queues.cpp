
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
//用数组模拟单调队列
int main() {
    cin.tie(0)->sync_with_stdio(0);
    static int a[N];
    int n,L,X = INT_MAX;
    static int sMi[N], fMi, eMi;
    static int sMx[N], fMx, eMx;
    fMi = fMx = 1, eMi = eMx = 0;
    for (int i = 1; i <= n; i++) {
        while (fMi <= eMi && a[sMi[eMi]] >= a[i]) eMi--;
        while (fMx <= eMx && a[sMx[eMx]] <= a[i]) eMx--;
        sMi[++eMi] = sMx[++eMx] = i;
        //大神写法
        fMi += sMi[fMi] == i - L;
        fMx += sMx[fMx] == i - L;
        if (i >= L)
            X = min(X, a[sMx[fMx]] - a[sMi[fMi]]);
    }
    return 0;
}
