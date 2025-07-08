
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 203;
ll mod = (ll) 998244353;
int n,m,q,k;
int t[N];
int g[N][N];
void flyod(){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(g[i][j]>g[i][k]+g[j][k])
                g[i][j]=g[j][i]=g[i][k]+g[j][k];
    k++;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>t[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        if(i!=j)    g[i][j]=1e9;
   // for(int i=0;i<len;i++)g[i][i]=0;
    int x,y,z;
    for(int i=0;i<m;i++){
        cin>>x>>y>>z;
        g[x][y]=g[y][x]=z;
    }
    cin>>q;
    k=0;
    while(q--){
        cin>>x>>y>>z;
        while(z>=t[k]&&k<n)flyod();
        if(t[x]>z||t[y]>z||g[x][y]==1e9)cout<<-1<<endl;
        else
            cout<<g[x][y]<<endl;
    }
    return 0;
}
