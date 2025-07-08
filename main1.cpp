#include <bits/stdc++.h>
using namespace std;
#define int long long
int a,b;
signed main() {
   // std::cin.tie(0)->sync_with_stdio(0);
    int tt=0;
    scanf("%lld",&tt);
    while(tt--)
    {
        scanf("%lld%lld",&a,&b);
        int gd=__gcd(a,b);
       // int as=b/gd;
       int ans=b;
        while(ans%gd==0&&gd!=1)
        {

           ans/=gd;
            gd=__gcd(ans,a);
        }
        //int pw=ans/__gcd(a,ans);
        if(__gcd(a,ans)==1&&__gcd(b,ans)>1)
        printf("%lld\n",ans);
        else printf("-1\n");



    }

    return 0;
}