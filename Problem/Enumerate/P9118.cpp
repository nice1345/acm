#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,k,x=0,y,t,op;cin>>n>>k;
    unordered_set<int>h;
    for(int i=2;i*i<=n/i;i++){
        t=i*i;
        while(t<=n/i){
            t*=i;op=2;
            if(op>=k&&!h.count(t)){
                h.insert(t);
                y= sqrt(t);
                if(y*y==t)x++;
            }
        }
    }
    if(k==1)cout<<n;
    else if(k>2)cout<<(int)h.size()+1ll;
    else cout<<(int)h.size()-x+ (int)sqrtl(n);
    return 0;
}