
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;

template<const int T>
struct ModInt {
    const static int mod = T;
    int x;
    ModInt(int x = 0) : x(x % mod) {}
    ModInt(long long x) : x(int(x % mod)) {}
    int val() { return x; }
    ModInt operator + (const ModInt &a) const { int x0 = x + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    ModInt operator - (const ModInt &a) const { int x0 = x - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    ModInt operator * (const ModInt &a) const { return ModInt(1LL * x * a.x % mod); }
    ModInt operator / (const ModInt &a) const { return *this * a.inv(); }
    bool operator == (const ModInt &a) const { return x == a.x; };
    bool operator != (const ModInt &a) const { return x != a.x; };
    void operator += (const ModInt &a) { x += a.x; if (x >= mod) x -= mod; }
    void operator -= (const ModInt &a) { x -= a.x; if (x < 0) x += mod; }
    void operator *= (const ModInt &a) { x = 1LL * x * a.x % mod; }
    void operator /= (const ModInt &a) { *this = *this / a; }
    friend ModInt operator + (int y, const ModInt &a){ int x0 = y + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    friend ModInt operator - (int y, const ModInt &a){ int x0 = y - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    friend ModInt operator * (int y, const ModInt &a){ return ModInt(1LL * y * a.x % mod);}
    friend ModInt operator / (int y, const ModInt &a){ return ModInt(y) / a;}
    friend ostream &operator<<(ostream &os, const ModInt &a) { return os << a.x;}
    friend istream &operator>>(istream &is, ModInt &t){return is >> t.x;}

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while(n){
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0;
        while (b) {
            int t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return u;
    }

};
using mint = ModInt<998244353>;



//ll mod = (ll) 998244353;
__int128 mod1=998244353;

inline __int128 readint128(){
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * (__int128)10 + (__int128)(ch - '0');
        ch = getchar();
    }
    return x * f;
}

inline void writeint128(__int128 x){
    if(x < 0){
        putchar('-');x = -x;
    }
    if(x > 9)
        writeint128((x / (__int128)10));
    putchar(x % 10 + '0');
}

struct i128{
 __int128 vaule;
    i128 operator+(const i128&b) const{
        return {(vaule+b.vaule)%mod1};
    }
    i128 operator-(const i128&b) const{
        return {(vaule-b.vaule+mod1)%mod1};
    }
    i128 operator*(const i128&b) const{
        return {vaule*b.vaule%mod1};
    }
    i128 operator%(const i128&b) const{
        return {vaule%b.vaule};
    }
    };
i128 mod={mod1};
i128 qmi(i128 a,i128 b){
    i128 res={1},p=a%mod;
    while (b.vaule>0){
        if(b.vaule&1)res=res*p%mod;


    }
}

int main() {
cin.tie()->sync_with_stdio(0);
i128 a,b={8};
a.vaule=7;
a=a*b;

    writeint128(a.vaule);




    return 0;
}
