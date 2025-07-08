#include<bits/stdc++.h>
using namespace std;
void solve() {
    int n,x;cin>>n>>x;
    int ans=0;
    for(int a=1;a<=n;a++)
        for(int b=1;b<=n/a;b++){
            //这儿可能有负值，忘考虑泪两行
            int c=max(min((n-a*b)/(a+b),x-a-b),0);
            ans+=c;
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

