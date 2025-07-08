#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N=1000005;
int n,ne,h[5005],mex;
ll f[5005];
int hh[5005],tree[5005];
void solve(){
    cin>>n;
    for(int i=0;i<=n;i++){
        h[i]=0;f[i]=2147483647;
    }
    f[0]=0;
    for(int i=1;i<=n;i++) {
        cin>>ne;
        if(ne<=n)h[ne]++;
    }
    for(int i=0;i<=n;i++)
        if(!h[i]){
            mex=i;break;
        }
    ///此题要从前往后dp
    ///当前mex为i时,最优策略,直接比较下一个要删个数
    for(int i=1;i<=mex;i++){
        ///降序删 注意只有mex是第一个选的删除的个数减一
        for(int j=0;j<i;j++)
            f[i]=min(f[i],(f[j]+(ll)(h[j]-(i==mex))*(ll)i));
    }
    cout<<f[mex]<<endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}




