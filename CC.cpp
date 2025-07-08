#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vec vector
#define i128 __int128
const int N=1e6;
const int mod=998244353;
int i2;
int qmi(int a,int b){
    a%=mod;
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void solve() {
//    int n;cin>>n;
//    int h=0;
//    int last=0;
//    for(int i=0;i<n;i++){
//        int ne;cin>>ne;
//        if(ne>0)last++;
//        else{
//            if(last){
//                h++;
//                last=0;
//            }
//        }
//    }
//    if(last){
//        h++;
//        last=0;
//    }
//    if(h>1){
//        cout<<2<<"\n";
//    }
//    else if(h==1)cout<<"1\n";
//    else cout<<"0\n";
}

signed main() {
    i2= qmi(2ll,mod-2ll);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    cout<<setiosflags(ios::fixed)<<setprecision(10);
    int t=1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}