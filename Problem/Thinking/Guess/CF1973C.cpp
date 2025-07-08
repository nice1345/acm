#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ll long long
#define pii array<int,2>
#define vec vector
const int N=200005;
const int mod=998244353;
/**
 省去优先队列
 * */
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while (_--){
        int n;
        cin>>n;
        vector<int>v(n+1),loc(n+1),ans(n+1);
        for(int i=1;i<=n;i++){
            cin>>v[i];
            loc[v[i]]=i;
        }
        int mn=n/2;
        int mx=n;
        for(int i=1;i<=n;i++){
            if(loc[i]%2 == loc[1]%2) ans[loc[i]]=mn--;
            else ans[loc[i]]=mx--;
        }
        for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
        cout<<endl;
    }
    return 0;
}