#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
#define vi vec<int>
#define vb vec<bool>
#define vs vec<string>
#define vc vec<char>
#define vvi vec<vec<int>>
#define vsi vec<basic_string<int>>
#define si basic_string<int>
#define order(vv)  sort(vv.begin(),vv.end())
#define eu(vv) vv.erase(unique(vv.begin(),vv.end()),vv.end());
#define gg(nn) vec<basic_string<int>>g(nn+1,basic_string<int>())
#define cn int n;cin>>n;
#define A0 vec<int>a(n);for(int &i:a)cin>>i;
#define A1 vec<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];
const int N = 2e5+5;
const int mod =  998244353;
//const int mod =1e9+7;
int ne;
/**
 贪心思想
 先把a填到最大，用剩余的把a+1填到最大
 然后把a替换为a+1
 * */
void solve() {
    int n,m;cin>>n>>m;
    A0
    map<int,int>mp;
    set<pii>h;
    for(int i=0;i<n;i++){
        cin>>ne;mp[a[i]]=ne;
        h.insert({a[i],a[i]+1ll});
    }
    int ans=0;
    for(auto [q,w]:h){
        int sum1=mp[q],sum2=mp[w];
        ans=max(ans,min(m/q,sum1)*q);
        int q1=min(m/q,sum1),w1=min((m-q1*q)/w,sum2),num=m-q*q1-w*w1;
        num=min({num,q1,sum2-w1})+q*q1+w*w1;
        ans=max(ans,num);
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

