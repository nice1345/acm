
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
ll mod=(ll)998244353;
int cnt=0;
vector<int>primes;
bool sg[N];
void get_primes(int x){
    sg[1]=true;
    for(int i=2;i<=x;i++){
        if(!sg[i]){
            primes.emplace_back(i);cnt++;
        }
        for(int j=0;j<cnt&&primes[j]<=x/i;j++){
            sg[primes[j] * i]=true;
            /**
            确保只会被最小质数筛去
            i % primes[j] == 0,primes[j+1] * i的最小质数是i
            i % pri[j] == 0
            换言之，i 之前被 pri[j] 筛过了
            由于 pri 里面质数是从小到大的，所以 i乘上其他的质数的结果一定会被
            pri[j]的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
            掉就好了
            */
            if(i%primes[j]==0)break;
        }
    }
}

      /**
       欧拉函数
      概念：f(N)为1~N中与N互质的个数称为N的欧拉函数
      如果 N = p1^c1 * p2^c2 * ... *pk^ck;
      f(N)=N*(1-1/p1)*...*( 1-1/pk);
      */
      int ne;
      int eulers[N];
      void get_eulers(int x){
          sg[1]=true;
          for(int i=2;i<x;i++){
              if(!sg[i]){
                 eulers[i]=i-1; primes.push_back(i);cnt++;
              }
              for(int j=0;j<cnt&&primes[j]<=x/i;j++){
                  ne=primes[j]*i;
                  sg[ne]=true;
                  if(i%primes[j]==0){
                      eulers[ne]=eulers[i]*primes[j];
                      break;
                  }
                  eulers[ne]=eulers[i]*eulers[primes[j]];
              }
          }
      }

/**
莫比乌斯函数
len==1时,mobius(len)=1;
len==p1*p2*...pk时(每个质数的幂都为1),mobius(len)=-1^(k);
其他情况都为0;
*/
int mobius[N];
 void get_mobius(int x){
     sg[1]=true;
    mobius[1]=1;
    for(int i=2;i<x;i++){
        if(!sg[i]){
            mobius[i]=-1; primes.push_back(i);cnt++;
        }
        for(int j=0;j<cnt&&primes[j]<=x/i;j++){
            ne=primes[j]*i;
            sg[ne]=true;
            mobius[ne]=-mobius[i];
            if(i%primes[j]==0){
                mobius[ne]=0;
                break;
            }
        }
    }
 }
int main() {


    return 0;
}
