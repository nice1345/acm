#include<bits/stdc++.h>
using namespace std;
int n,cnt;
long long ans=0;
template<typename T>
struct BIT{
    int len;vector<T>tree;
    BIT(int n){tree.resize(n);len=n;}
    void add(int i,T v){for(;i<len;i+=i&-i)tree[i]+=v;}
    T query(int i){T res=0;for(;i;i-=i&-i)res+=tree[i];return res;}
};
//直接去看官解
void solve() {
cin>>n;
map<int,int>id;
vector<int>a(n),b(n);
for(int i=1;i<=n;i++){
    cin>>b[i-1];id[b[i-1]]=i;
}
for(int &i:a)cin>>i;
vector<int>a1=a,b1=b;
sort(a1.begin(),a1.end());
sort(b1.begin(),b1.end());
if(a1!=b1){
    cout<<"NO\n";
    return;
}
BIT<int> h(n+10);
ans=0;
for(int i=n-1;i>=0;i--){
    cnt=id[a[i]];
    ans+=h.query(cnt-1);
    h.add(cnt,1);
}
//cout<<sum<<"\n";
if(ans&1)cout<<"NO\n";
else cout<<"YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
