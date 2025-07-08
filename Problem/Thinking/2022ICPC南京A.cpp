//题解：https://blog.csdn.net/Euphria/article/details/132240658
//跟题解思路一样，但自个写的太复杂了，调了好久

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N=13000005;
int n,m,k,x,y,l,r,u,d,nx,ny;
string s;

void solve(){
    cin>>n>>m>>k;
    cin>>s;
    vector<vector<int>>h(n*2+10,vector<int>(m*2+10,0));
    x=n+5;y=m+5;
    l=r=u=d=nx=ny=0;
    h[x][y]=1;
    for(int i=0;i<s.size();i++){
        if(s[i]=='U'){
            x++;nx--;
            l=min(l,nx);
        }
        else if(s[i]=='D'){
            x--;nx++;
            r= max(r,nx);
        }
        else if(s[i]=='L'){
            y++;ny--;
            u= min(u,ny);
        }
        else{
            y--;ny++;
            d= max(d,ny);
        }
        if(x>=0&&x<n*2+10&&y>=0&&y<m*2+10)
            h[x][y]=1;
    }

//二维前缀和
    for(int i=0;i<n*2+5;i++)
        for(int j=1;j<m*2+5;j++)
            h[i][j]+=h[i][j-1];

    for(int i=1;i<n*2+5;i++)
        for(int j=0;j<m*2+5;j++)
            h[i][j]+=h[i-1][j];

    l=-l+1;r=n-r;u=-u+1;d=m-d;

    int sum=(r-l+1)*(d-u+1);

    if(sum==0||(r-l+1)<0||(d-u+1)<0){
        if(k==0){
            cout<<(n*m)<<endl;
        }
        else cout<<0<<endl;
    }
    else{
        int x1,y1,x2,y2;
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                x1=l+(n+5-i),y1=u+(m+5-j);
                x2=r+(n+5-i),y2=d+(m+5-j);
                int sum1=h[x2][y2]-h[x1-1][y2]-h[x2][y1-1]+h[x1-1][y1-1];

                if(sum1==(sum-k))ans++;
            }
        }
        cout<<ans<<endl;
    }
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