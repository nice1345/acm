#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define vec vector
const int mod=12345678;
int n,m,num=0,sum,ans=0;
char mp[4][7];
void calc(){

}
void dfs(int x,int y){
    if(x==n)calc();

}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='X')num++;
        }
    sum=num;
    return 0;
}

