#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<int>d(50,0);
    for(int i=0;i<n;i++){
        int ne;
        cin>>ne;
        while(ne){
            int w=__lg(ne);
            if(!d[w]){
                d[w]=ne;
                break;
            }
            ne^=d[w];
        }
    }
    int ans=0;
    for(int w=49;w>=0;w--)
        if((ans&(1ll<<w))==0)ans^=d[w];
    cout<<ans<<"\n";
    return 0;
}