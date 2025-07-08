#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5000;

uint16_t minp[N + 2], ord[N + 1], last[N + 1];
bool hv[N + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int tc = (cin >> tc, tc); tc--; ) {
        int n; cin >> n;
        vector<uint16_t> a(n);
        for (auto& a: a) cin >> a;
        fill_n(last, n + 1, 0);
        fill_n(minp + 1, n + 1, n + 1);
        int sz = 0;
        for (int i = 0; i < n; ++i) {
            for (int mex = 0; mex <= i + 1; ++mex) if (minp[mex] == i) ord[sz++] = mex;
            ord[sz] = n + 1;
            for (int mex = 0, j = i; ~j; --j) {
                hv[a[j]] = 1;
                if (a[j] != mex) continue;
                do ++mex; while (hv[mex]);
                while (minp[ord[last[mex]]] <= j) {
                    int v = mex ^ ord[last[mex]++];
                    minp[v] = min(+minp[v], i + 1);
                }
            }
            fill_n(hv, n + 1, 0);
        }
        int ans = n;
        while (minp[ans] > n) --ans;
        cout << ans << '\n';
    }
}
