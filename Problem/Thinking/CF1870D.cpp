#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
const int N=1000005;
ll mod=(long)998244353;
int T;

ll n,k,t,tree[N],i;
void solve(){
    cin>>n;
    for(i=1;i<=n;i++)cin >> tree[i];
    cin>>k;t=1e18;
    ///重要理解就是它满足差分的性质
    ///先后缀min,在差分,tree[i]表示  [i,len]的min - [i-1,len]的min
    for(i=n;i;i--)tree[i - 1]=min(tree[i - 1], tree[i]), tree[i]-=tree[i - 1];
    for(i=1;i<=n;i++){
        ///余下的k(钱)可以帮助add1的范围增加,增加多少,增加k/(差分后的)tree[i]
        if(tree[i])t=min(t, k / tree[i]);
        cout<<t<<' ';
        k-= t * tree[i];
    }
    cout<<'\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    //T=1;
    while(T--){
        solve();
    }

    return 0;
}




