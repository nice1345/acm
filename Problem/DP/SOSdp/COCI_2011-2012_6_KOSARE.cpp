//题目链接:https://www.luogu.com.cn/problem/P6442
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N =(1<<20);
ll mod = (ll)1e9+7;
ll dp[N+5];

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
int n,k,ne,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&k);
        int sum=0;
        for(int j=0;j<k;j++){
            scanf("%d",&ne);
            ne--;
            sum|=(1<<ne);
        }
        dp[sum]++;
    }
for(int w=0;w<20;w++){
    for(int i=0;i<N;i++){
        if((i>>w)&1)dp[i]+=dp[i^(1<<w)];
    }
}
for(int i=0;i<N;i++)dp[i]= (qmi(2,dp[i])-1+mod)%mod;

//第二种解法:容斥(困难)
//题读错了,没多难,类比求欧拉函数的公式的容斥
ll sum=0;
for(int i=0;i<(1<<m);i++){
    int no=__builtin_popcount(i);//i在二进制下1的数量
    if(no%2==m%2)sum=(sum+dp[i])%mod;
    else sum=(sum-dp[i]+mod)%mod;
}
    printf("%lld\n",sum);
    return 0;


//第一种解法:容斥(普通)
for(int w=0;w<20;w++){
    for(int i=0;i<N;i++){
        if((i>>w)&1)dp[i]=(dp[i]-dp[i^(1<<w)]+mod)%mod;
    }
}
printf("%lld\n",dp[((1<<m)-1)]);





    return 0;
}
