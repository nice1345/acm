#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
//题解：https://www.cnblogs.com/luckyblock/p/18353021#e1
int n,cnt,_;
long long a[N],arr[N];
int ls[N],rs[N],st[N];
bool flag;
void dfs(int cur,int fa,int l,int r){
    if(arr[r]-arr[l-1]>=a[fa]){
        cnt++;
        if(ls[cur])dfs(ls[cur],cur,l,cur-1);
        if(rs[cur])dfs(rs[cur],cur,cur+1,r);
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>_;
    while(_--){
        cin>>n;cin>>n;
        cnt=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            arr[i]= a[i] + arr[i - 1];
            flag=0;
            while(cnt!=0&&a[i]>a[st[cnt]])cnt--,flag=1;
            rs[st[cnt]]=i;
            if(flag)ls[i]=st[cnt + 1];
            st[++cnt]=i;
        }
        cnt=0;
        dfs(st[1],0,1,n);
        cout<<cnt<<"\n";
    }
    return 0;
}
