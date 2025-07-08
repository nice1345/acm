/*
 树状数组的某一条链
 v1-v2-v3-v4;
 v1的值在父节点留下了多少倍
   v1 v2 v3 v4
a:  1 0 0 0
f1: 1 1 1 1
f2: 1 2 3 4
f3: 1 3 6 10
f3: 1 4 10 20
假设深度差为d
子节点在父节点的倍数为(d+k-1,k-1)==(d+k-1,d);(k-1会很大，d最大为log(n))
设深度差为d的倍数为c[d];
 c[1]=k=(k,1);
 c[d-1]=(d+k-2,d-1)
 c[d]=(d+k-1,d)
 c[d]=c[d-1]*(d+k-1)/d;

 * **/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
const int N=200005;
const int mod=998244353;
ll qmi(ll a,ll b){
    ll  res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}
signed main( )
{
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while (_--){
        int n,k;cin>>n>>k;
        vec<int>c(35,0);
        c[1]=k;
        for(int i=2;i<35;i++){
            c[i]=c[i-1]*(i+k-1)%mod;
            c[i]=c[i]*(int)qmi(i,mod-2)%mod;
        }
        vec<int>b(n+1);
        for(int i=1;i<=n;i++)cin>>b[i];

        for(int i=1;i<=n;i++){
            b[i]%=mod;b[i]+=mod;b[i]%=mod;
            cout<<b[i]<<" ";
            //i+(i&-1) 这一定要加括号啊
            for(int j=i+(i&-i),d=1;j<=n;j+=j&-j,d++)
                b[j]=(b[j]-b[i]*c[d]%mod+mod)%mod;
        }
        cout<<"\n";
    }


    return 0;
}