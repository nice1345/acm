
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1<<20;
ll mod = (ll)1e9+7;
ll dp[1<<20+5];

ll qmi(ll a,ll b){
    ll res=1,p=a%mod;
    while(b){
        if(b&1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}

int main() {
    int n,ne;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&ne);
        dp[ne]++;
    }


    //求i的超集
for(int w=0;w<20;w++){
    for(int i=0;i<N;i++){
        if(!((i>>w)&1))dp[i]=(dp[i]+dp[(1<<w)^i])%mod;
    }
}


//i的超集构成的集合(不分顺序)全部&操着后定为i的超集
//全部&操着后定为i的超集的方案数为2^(i的超集数)-1;
for(int i=0;i<N;i++){
    dp[i]= (qmi(2,dp[i])-(ll)1)%mod;
    dp[i]=(dp[i]+mod)%mod;
}


//全部&操作一定为i的方案数==(全部&操作一定为i的超集的方案数)-(全部&操作一定为i的真超集(为i的超集但不是i)的方案数)
    for(int w=0;w<20;w++){
        for(int i=0;i<N;i++){
            if(!((i>>w)&1))dp[i]=(dp[i]-dp[(1<<w)^i]+mod)%mod;
        }
    }
    /**
     实测发现
     w从0到19,i从0到1<<20-1,
     w从19到1,i从0到1<<20-1,
     w从0到19,i从1<<20-1到0,
     w从19到0,i从1<<20-1到0,
     四种遍历方式都是可以的,只要保证w(维数)在外层循环就行
     **/
    printf("%lld\n",dp[0]);
    return 0;
}
