#include<bits/stdc++.h>
using namespace std;
/*
 连续子段绝对值最大意味着变化量最大
 意味着区间内最大前缀减去最小前缀
 nb
 * */
int main() {
    long long n,a,s[500005]={0},q,l,r,k;
    long long d[500005][25]={0},x[500005][25]={0};
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&a);
        d[i][0]=x[i][0]=s[i]=s[i-1]+a;
    }
    scanf("%lld",&q);
    for(int i=1;i<=log2(n);i++)
        for(int j=0;j+(1<<i)-1<=n;j++) {
            d[j][i]=max(d[j][i-1],d[j+(1<<(i-1))][i-1]);
            x[j][i]=min(x[j][i-1],x[j+(1<<(i-1))][i-1]);
        }
    while(q--) {
        scanf("%lld%lld",&l,&r);
        l--;
        k=log2(r-l+1);
        printf("%lld\n",abs(max(d[l][k],d[r-(1<<k)+1][k])-min(x[l][k],x[r-(1<<k)+1][k])));
    }
}