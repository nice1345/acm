/**
 所有操作均不改变两个元素的行列相对性
 两个元素在a中处于同行，那么在b中也处于同行
 两个元素在a中处于同列，那么在b中也处于同列
 否则，输出NO
 * */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
#define node array<int,2>
const int N=200005;
const int mod=998244353;
int n,m;
void solve(){
    cin>>n>>m;
    vec<vec<int>>a(n,vec<int>(m)),b(n,vec<int>(m));
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>a[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>b[i][j];
    map<int,vec<int>>ar,br;
    for(int i=0;i<n;i++){
        vec<int>no;
        for(int j=0;j<m;j++)
            no.emplace_back(a[i][j]);
        sort(no.begin(),no.end());
        ar[no[0]]=no;
    }
    for(int i=0;i<n;i++){
        vec<int>no;
        for(int j=0;j<m;j++)
            no.emplace_back(b[i][j]);
        sort(no.begin(),no.end());
        br[no[0]]=no;
    }
    auto ch=[&](vec<int> q,vec<int> w){
        int l=q.size();
        for(int i=0;i<l;i++)
            if(q[i]!=w[i])
                return 0;
        return 1;
    };
    for(auto [i,j]:ar){
        if(!br.count(i)||!ch(j,br[i])){
            cout<<"NO\n";
            return;
        }
    }
    map<int,vec<int>>ac,bc;
    for(int i=0;i<m;i++){
        vec<int>no;
        for(int j=0;j<n;j++){
            no.emplace_back(a[j][i]);
        }
        sort(no.begin(),no.end());
        ac[no[0]]=no;
    }
    for(int i=0;i<m;i++){
        vec<int>no;
        for(int j=0;j<n;j++){
            no.emplace_back(b[j][i]);
        }
        sort(no.begin(),no.end());
        bc[no[0]]=no;
    }
    for(auto [i,j]:ac){
        if(!bc.count(i)||!ch(j,bc[i])){
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }

    return 0;
}
