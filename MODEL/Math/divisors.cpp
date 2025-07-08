#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
ll mod=(ll)998244353;
/**
 如果 N = p1^c1 * p2^c2 * ... *pk^ck(p是质因子,c是质因子的幂)
约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)
约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)
 * */

/**约数个数*/
int Approximate_num(int x){
    int ans=1 ;
    for (int i=2;i<=x / i; i ++ )
        if(x%i==0){
            int s=1;
            while(x%i==0)x/=i,s+=1;
            ans*=s ;
        }
    if(x>1)
        ans*=2;
    return ans ;
}

/**约数之和*/
int Approximate_sum(int x){
    int ans=1 ;
    for (int i=2;i<=x / i; i ++ )
        if(x%i==0){
            int s=1;
            while(x%i==0)x/=i,s=s*i+1;
            ans*=s ;
        }
    if(x>1)
        ans*=x+1;
    return ans ;
}

int main() {


    return 0;
}




