#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n , m , k;
int up(int a,int b){
    if(a <= b) return 1;
    return (a + b - 1) / b;
}
ll sum(int l,int r,int k){
    return 1LL*(l + r)*((r-l)/k + 1) / 2;
}
ll get(int n,int k){
    int p = 0 , r = 0;
    if(k == 1) return 0;
    ll ans = 0;
    int d = n / __gcd(n , k);
    while(r < d) {
        ///next round sg r+1 -th
        int lm = (n - p) / k ;
        lm = min(d , r + lm) - r;
        ///last for [r+1 , r+lm] rounds

        int x = up(r - p + 1 , k - 1) ;
        /// [r+x , r+lm] winning
        if(x <= lm) ans += sum(p + x*k , p+lm*k , k);
        p = (p + lm*k) - n;
        r += lm;
    }
    return ans;
}
void solv(){
    cin >> n >> m;
    ll sol = -1;
    int ans ;

    for(int k = 1;k <= m;k++) {
        ll d = get(n , k);
        if(d > sol) {sol = d , ans = k;}
    }
    cout << ans << '\n';
    return;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    while(T--) solv();
    return 0;
}



//jingly代码
//#include <bits/stdc++.h>
//
//using i64 = long long;
//
//int main() {
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//
//    int N, M;
//    std::cin >> N >> M;
//
//    i64 sum = 0;
//    int k = 1;
//    for (int K = 1; K <= M; K++) {
//        i64 res = 0;
//        int g = std::gcd(K, N);
//        for (int d = 0; d < K; d++) {
//            i64 lo = (1LL * d * N + K - 1) / K;
//            i64 hi = std::min(1LL * N / g - 1, (1LL * (d + 1) * N - 1) / K);
//            if (K == 1) {
//                hi = -1;
//            } else {
//                lo = std::max(lo, 1LL * d * N / (K - 1) + 1);
//            }
//            if (lo <= hi) {
//                res += 1LL * (lo + hi) * (hi - lo + 1) / 2 * K;
//                res -= 1LL * (hi - lo + 1) * d * N;
//            }
//        }
//        if (g > 1) {
//            res += N;
//        }
//        if (res > sum) {
//            sum = res;
//            k = K;
//        }
//    }
//    std::cout << k << "\len";
//
//    return 0;
//}