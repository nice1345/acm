#include <bits/stdc++.h>
#define pii pair<int,int>
#define vec vector
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N = 1e5 + 5;
int n,m,k,x,y,fx,fy,ma=0,l,r,mid;
pair<int,int> lo[4]={{0,1},{0,-1},{1,0},{-1,0}},
        oo[8]{{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{-1,1},{1,-1}};
bool falg= false;
string s;
void solve(){
    cin>>n>>m>>k;
    vec<vec<int>>g(n+5,vec<int>(m+5,0));
    vec<vec<bool>>vis(n+5,vec<bool>(m+5, false));
    queue<pii>q;vec<pii>p,v;
    for(int i=1;i<=n;i++){
        cin>>s;
        for(int j=1;j<=m;j++){
            if(s[j-1]=='v'){
                g[i][j]=-1;
                q.push({i,j});
                v.push_back({i,j});
            }
            if(s[j-1]=='#')p.push_back({i,j});
        }
    }
    while (!q.empty()){
        auto no=q.front();q.pop();
        for(auto o:lo){
            x=no.first+o.first;y=no.second+o.second;
            if(x==0||x==n+1||y==0||y==m+1||g[x][y]!=0)continue;
            if(g[no.first][no.second]==-1)g[x][y]=1;
            else g[x][y]=g[no.first][no.second]+1;
            ma=max(ma,g[x][y]);
            q.push({x,y});
        }
    }

    for(pii o:p)g[o.first][o.second]=-2;
    for(pii o:v)g[o.first][o.second]=0;
    auto bfs= [&](int dis) {
        while (!q.empty())q.pop();
        for(pii o:p){
            q.push(o);
            vis[o.first][o.second]=true;
        }
        falg= true;
        while(!q.empty()){
            auto no=q.front();q.pop();
            if(no.first==1||no.first==n||no.second==m||no.second==1){
                falg= false;break;
            }
            for(auto o:oo){
                x=no.first+o.first;y=no.second+o.second;
                if(!vis[x][y]){
                    q.push({x,y});vis[x][y]=true;
                }
            }
        }
    };

    function<void(pii,int)>dfs=[&](pii no,int q3){
        vis[no.first][no.second]=true;
        for(auto o:lo){
            x=no.first+o.first;y=no.second+o.second;
            if(x==0||x==n+1||y==0||y==m+1||g[x][y]<q3||vis[x][y])continue;
            dfs({x,y},q3);
        }
    };
    while(k--){
        cin>>fx>>fy;
        r=g[fx][fy];l=0;
        while(l<=r){
            mid=(l+r)>>1;
            for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)vis[i][j]= false;
            dfs({fx,fy},mid);
            bfs(mid);
            if(falg)l=mid+1;
            else r=mid-1;
        }
        cout<<r<<"\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    while (T--)solve();
    return 0;
}
