#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n,k,f=0;cin>>n>>k;
    vector<int>b(n+1,0),c(30,-1);
    for(int i=2;i<=n;i++)cin>>b[i],b[i]^=b[i-1];
    for(int i=1;i<n;i++){
        for(int j=29;j>=0;j--){
            //a[i]在这一位与a[i+1]不同,它们在这一位与a[1]的异或也不同
            //只能是a[i+1]在这一位是1,a[i]在这一位是0
            //所以a[1]只能是1
            if((b[i]>>j&1)!=(b[i+1]>>j&1)){
                if(c[j]==-1)c[j]=(b[i]>>j&1);
                else if(c[j]!=(b[i]>>j&1))f=1;
                break;
            }
        }
    }
    if(f)cout<<-1<<'\n';
    else {
        //极简代码
        k--;//二进制是从0开始的
        int ans=0,p=1;
        for(int i=0,j=0;i<=29;i++){
            if(c[i]==1)ans|=1<<i;
            else if(c[i]==-1){
                if(k>>j&1)ans|=1<<i;
                j++;
                p*=2;
            }
        }
        if(k>=p)cout<<-1<<'\n';
        else for(int i=1;i<=n;i++)cout<<(ans^b[i])<<" \n"[i==n];
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int T;cin>>T;
    while(T--)solve();
    return 0;
}