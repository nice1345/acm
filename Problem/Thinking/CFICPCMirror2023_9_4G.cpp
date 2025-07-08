//https://codeforces.com/contest/1866/problem/G
#include<bits/stdc++.h>
#define ll long long
#define pii pair<ll,ll>
#define fi first
#define se second
using namespace std;
const int N=200005;
ll n;
ll tree[N],d[N];
vector<pair<ll,ll> >vec[N];
priority_queue<pii,vector<pii>,greater<pii> >q;
bool chk(ll lim){
    while(!q.empty())q.pop();
    for(ll i=1;i<=n;i++){
        for(auto pr:vec[i]){
            q.push(pr);
        }
        ll tmp=lim;
        while(tmp){
            if(!q.size())break;
            pair<ll,ll>p=q.top();q.pop();
            if(i>p.first)return 0;
            if(tmp>=p.second){
                tmp-=p.second;
            }
            else{
                p.second-=tmp;tmp=0;
                q.push(p);
                break;
            }
        }
    }
    if(!q.empty())return 0;
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(ll i=1;i<=n;i++)cin >> tree[i];
    for(ll i=1;i<=n;i++){
        cin>>d[i];
        ll l=i-d[i],r=i+d[i];
        l=max(l,1ll);r=min(r,n);
        if(tree[i])vec[l].push_back({r, tree[i]});
    }
    ll l=0,r=1e9;
    while(l<=r){
        int mid=l+r>>1;
        if(chk(mid))r=mid-1;
        else l=mid+1;
    }
    cout<<r+1<<"\n";
    return 0;
}