
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ll long long
#define vec vector
#define pii array<int,2>
const int N = 1000005;
ll mod = (ll) 998244353;
//设置生成随机数的区间
int l=1e8+7,r=mod-2;
// 使用当前的稳定时钟时间作为随机数生成器的种子
std::mt19937_64 rng((unsigned long long)std::chrono::steady_clock::now().time_since_epoch().count());
// 创建一个在指定范围内的均匀分布
std::uniform_int_distribution<unsigned long long> dis(l,r);
//dis(rng);获取 如int base=dis(rng);
void solve() {
    cout<<dis(rng);
    //cout<<(1004535809<(int)INT_MAX);
}


vec<int>hash_base={29,31,131,1331};
vec<int>hash_mod={998244353,1000000007,167772161,469762049,754974721,1004535809};
struct hash_node{
    vec<int>node;
    hash_node operator * ( const hash_node& a)const{

    }
};
struct hash{

};


signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    //cin >> T;
    while (_--) {
        solve();
    }

    return 0;
}
