#include "cstdio"
#include "iostream"
#include "cstring"
#include <vector>
using namespace std;
int loc[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
char ne;
int n;
int gauss(vector<vector<int>> &g){
    int i,j,k;
    for(i=0,j=0;i<n*n&&j<n*n;i++,j++){
        k=i;
        for(;k<n*n;k++)
            if(g[k][j]) break;
        if(k==n*n) {i--;continue;}
        for(int t=j;t<=n*n;t++)
            if(i!=k) swap(g[i][t],g[k][t]);
        // if(!g[i][j]) {i--;continue;}
        for(k=i+1;k<n*n;k++){
            if(g[k][j])
                for(int t=j;t<=n*n;t++)
                    g[k][t]^=g[i][t];
        }
    }
    k=i;
    for(i=k; i<n*n; i++)
        if(g[i][n*n]) return -1;
    for(i=k-1; i>=0; i--)
        for(j=i+1; j<n*n; j++)
            g[i][n*n]^=(g[i][j]&g[j][n*n]);
    int ans=0;
    for(i=0;i<n*n;i++)
        if(g[i][n*n]==1)ans++;
    return ans;
}
/**
 * 题解：https://www.cnblogs.com/neopenx/p/4073466.html
 * */
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while(_--){
        cin>>n;
        vector<vector<int>> a(n*n,vector<int>(n*n+1,0));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                a[i*n+j][i*n+j]=1;
                for(int k=0;k<4;k++){
                    int x=i+loc[k][0],y=j+loc[k][1];
                    if(x<0||x>=n||y<0||y>=n)continue;
                    a[i*n+j][x*n+y]=1;
                }
            }

        for(int i=0;i<n*n;i++){cin>>ne;if(ne=='w')a[i][n*n]=1;}
        int pw=gauss(a);
        if(pw!=-1)cout<<pw<<"\n";
        else cout<<"inf\n";
    }
}
