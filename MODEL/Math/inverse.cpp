
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

ll inv[N];
void det_inv(){
    inv[1] = 1;
    for (ll i = 2; i < (ll)N; i++) {
        inv[(int)i] = (mod - mod / i) * inv[(int)(mod % i)] % mod;
        inv[(int)i]+=mod;
        inv[(int)i]%=mod;
    }
}


int main() {


    return 0;
}