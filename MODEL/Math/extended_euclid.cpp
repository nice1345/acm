

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;




int ex_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = ex_gcd(b, a % b, x, y);
    /**
     sum*x+(tree%sum)*y=gcd;
     (tree%sum+tree/sum*sum)*y+sum*(x-tree/sum*y)=gcd;
     对变化后的x,y
     x=y;
     y=x-tree/sum*y;
     */
    int temp = x;
    x = y;
    y = temp - a / b * y;
    return d;
}

bool liEu(int a, int b, int c, int& x, int& y) {
    int d = ex_gcd(a, b, x, y);
    if (c % d != 0) return 0;
    int k = c / d;
    x *= k;
    y *= k;
    return 1;
}

int main() {


    return 0;
}