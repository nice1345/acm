/**
 根号分治
 更快的思路：https://www.cnblogs.com/yoshinow2001/p/18170877
 更快又不懂：https://codeforces.com/contest/1968/submission/261755870
 * */
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
vector<int> nt;
unordered_map<string, int> p;
void build(string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i ++ ) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j += 1;
        pi[i] = j;
    }
    nt = pi;
}
int KMP(string &t, string &s) {
    if (p.count(s)) return p[s];
    build(s);
    int n = t.size(), m = s.size(), j = 0;
    int last = -1e9, ans = 0;
    for (int i = 0; i < n; i ++ ) {
        while (j > 0 && t[i] != s[j]) j = nt[j - 1];
        if (t[i] == s[j]) j += 1;
        if (j == m) {
            int head = i - m + 1;
            if (head >= last + m) {
                ans += 1;
                last = head;
            }
        }
    }
    return p[s] = ans;
}
void solve() {
    int n, ll, lr; cin >> n >> ll >> lr;
    string s; cin >> s;
    for (int i = ll; i <= lr; i ++ ) {
        int l = 0, r = n / i + 1;
        while (l + 1 != r) {
            int mid = l + r >> 1;
            string temp = s.substr(0, mid);
            if (KMP(s, temp) >= i) l = mid;
            else r = mid;
        }
        cout << l << ' ';
    }
    p.clear();
    cout << endl;

}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }

    return 0;
}
