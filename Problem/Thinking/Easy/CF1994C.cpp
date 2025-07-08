#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vec vector
//先找出每个l对应的最小r,然后发现所有片段都是可以连接的
void solve() {
    int n,x;cin>>n>>x;
    vec<int>a(n+1),b(n+5);
    for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
    int j=1;
    for(int i=1;i<=n;i++){
        while(j<=n&&a[j]-a[i-1]<=x)j++;
        if(j<=n)b[i]=j+1;
    }
    int ans=n*(n+1ll)/2ll;
    for(int i=n;i>0;i--){
        if(b[i])b[i]=b[b[i]]+1;
        ans-=b[i];
    }
    cout<<ans<<"\n";
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

