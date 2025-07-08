#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define vec vector
/*
 麻了，居然是鸽巢原理
 倒着想，加边顺序反着来，只要是棵树，加边顺序正反无所谓，先找第n-1条边该怎么加
 刚开始时，每个点自成一个联通块，每个联通块仅用联通块里的一个点作为代表
 加第i条边就有i+1个点的代表，最多有i+1种a[i]，取模i(a[i]%i)就只有i种结果
 那必然存在两个点模i同余
 那么答案必然存在
 暴力求就行
 * */
void solve() {
    int n;cin>>n;
    vec<int>a(n);for(int &i:a)cin>>i;
    vec<int>p(n);
    iota(p.begin(),p.end(),0);
    vec<pii>ans;
    for(int i=n-1;i;i--){
        vec<int>h(i,-1);
        for(int j:p){
            if(h[a[j]%i]!=-1){
                ans.emplace_back(j,h[a[j]%i]);
                p.erase(std::lower_bound(p.begin(), p.end(),j));
                break;
            }
            h[a[j]%i]=j;
        }
    }
    reverse(ans.begin(),ans.end());
    cout<<"YES\n";
    for(auto [i,j]:ans)cout<<i+1<<" "<<j+1<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

