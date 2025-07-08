#include<bits/stdc++.h>
using namespace std;
bool gauss(vector<vector<double>> &g){
    int n=(int)g.size()-1;
    for(int j=1;j<=n;j++){
        int max_r=j;
        for(int i=j+1;i<=n;i++)
            if(fabs(g[i][j])> fabs(g[max_r][j]))max_r=i;
        if(fabs(g[max_r][j])<(double)1e-7)return false;
        if(max_r!=j)
            for(int i=j;i<=n+1;i++)
                swap(g[j][i],g[max_r][i]);
        double div=g[j][j];
        for(int i=j;i<=n+1;i++)
            g[j][i]/=div;
        for(int i=1;i<j;i++){
            div=g[i][j];
            g[i][j]=0;
            for(int k=j+1;k<=n+1;k++)
                g[i][k]-=div*g[j][k];
        }
        for(int i=j+1;i<=n;i++){
            div=g[i][j];
            g[i][j]=0;
            for(int k=j+1;k<=n+1;k++)
                g[i][k]-=div*g[j][k];
        }
    }
    return true;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}