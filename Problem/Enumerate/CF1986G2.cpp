#include<bits/stdc++.h>
using namespace std;
#define vec vector
const int N = 5e5 + 5;
int n,g;
int x[N],y[N],a[N],sum[N];
vec<int>xp[N],yp[N],fac[N];
//题解：https://blog.csdn.net/weixin_44178736/article/details/140065875
void solve() {
cin>>n;
for(int i=1;i<=n;i++){
    xp[i].clear();
    yp[i].clear();
}
for(int i=1;i<=n;i++){
    cin>>a[i];
    g=__gcd(a[i],i);
    x[i]=a[i]/g;
    xp[x[i]].emplace_back(i);
    y[i]=i/g;
    yp[y[i]].emplace_back(i);
}
long long ans=0;
for(int yi=1;yi<=n;yi++){
    for(int xj=yi;xj<=n;xj+=yi)
        for(int j:xp[xj])sum[y[j]]++;
    for(int i:yp[yi])
        for(int yj:fac[x[i]])
            ans+=sum[yj];
    for(int xj=yi;xj<=n;xj+=yi)
        for(int j:xp[xj])sum[y[j]]--;
}
for(int i=1;i<=n;i++)
    if(x[i]%y[i]==0)ans--;
ans/=2ll;
cout<<ans<<"\n";
}

signed main() {
    for(int i=1;i<=500000;i++)
        for(int j=i;j<=500000;j+=i)
            fac[j].emplace_back(i);
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
