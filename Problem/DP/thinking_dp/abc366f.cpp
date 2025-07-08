#include<bits/stdc++.h>
using namespace std;
pair<int,int> a[200005];
long long f[11];
/**
 * 先以最优方式排序再dp
 * */
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;cin>>n>>k;
    for(int i=0;i<n;i++)cin>>a[i].first>>a[i].second;
    sort(a,a+n,[&](pair<int,int> &q,pair<int,int> &w){
        return q.first*w.second+q.second<w.first*q.second+w.second;
    });
    f[0]=1;
    for(int i=0;i<n;i++)
        for(int j=k;j>0;j--)
            if(f[j-1])
                f[j]=max(f[j],f[j-1]*(long long)a[i].first+(long long)a[i].second);
    cout<<f[k];
    return 0;
}
