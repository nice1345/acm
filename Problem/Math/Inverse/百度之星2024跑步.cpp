/*
 设1~n的lcm=m
 统计每个人跑的圈数m/i
 a<b   m/a-m/b
 统计i分别作为a,b的系数
 最后统计和
 */
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
const int N = 1e7+5;
const ll mod =  998244353;
int primes[N];
ll inv[N];
int cnt=0;
bool is[N];
int main()
{
    int n;cin>>n;
    inv[0]=inv[1]=1;
    ll lc=1,ans=n-1,val;
    for(int i=2;i<=n;i++){
        inv[i]=(mod-mod/(ll)i)*inv[(int)(mod%i)]%mod;
        inv[i]+=mod;inv[i]%=mod;
        ans=(ans+(ll)(n-2ll*i+1ll)*inv[i]%mod)%mod;
        if(!is[i]){
            primes[cnt++]=i;
            val=i;
            while(val<=(ll)(n/i))val*=(ll)i;
            lc=lc*val%mod;
        }
        for(int j=0;j<cnt&&primes[j]<=(n/i);j++){
            is[primes[j]*i]=true;
            if(i%primes[j]==0)break;
        }
    }
    ans=(ans+mod)%mod;
    ans=ans*lc%mod;
    cout<<ans;
    return 0;
}

