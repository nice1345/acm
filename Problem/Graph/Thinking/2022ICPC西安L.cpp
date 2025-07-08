//反链,最长反链:https://kewth.github.io/2020/07/15/%E6%9C%80%E9%95%BF%E5%8F%8D%E9%93%BE%E9%95%BF
//题解:https://blog.csdn.net/m0_62289613/article/details/130045410
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N=1000005;
int n;
vector<int>edge[N];
void solve(){
    cin>>n;
    for(int i=0;i<=n;i++)edge[i].clear();
    vector<int>f(n+1,0),d(n+1,0),du(n+1,0),mdu(n+1,0);
    for(int i=2;i<=n;i++){
        cin>>f[i];
        d[f[i]]++;
        edge[f[i]].push_back(i);
    }
    queue<int>q;
    q.push(1);
    int no,so;
    //获得节点深度
    while (!q.empty()){
        no=q.front();q.pop();
        for(int i:edge[no]){
            du[i]=du[no]+1;
            q.push(i);
        }
    }

    for(int i=1;i<=n;i++)if(!d[i])q.push(i);
    //获得节点子树中最大深度
    while (!q.empty()){
        no=q.front();
        q.pop();
        mdu[no]= max(mdu[no],du[no]);
        mdu[f[no]]= max(mdu[f[no]],mdu[no]);
        d[f[no]]--;
        if(!d[f[no]]&&no!=1)q.push(f[no]);
    }

    vector<int>fan(mdu[1]+5,0);

    for(int i=1;i<=n;i++)fan[mdu[i]-du[i]]++;

    int ans=mdu[1]+1;
    for(int i=0;i<mdu[1];i++){
        ans=min(ans,i+fan[i]);
    }
    cout<<ans<<endl;
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
