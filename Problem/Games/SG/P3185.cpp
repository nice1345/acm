#include<bits/stdc++.h>
using namespace std;
int sg[25],a[25],vis[25];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    sg[0]=0;
    for(int i=1;i<22;i++){
        for(int j=0;j<i;j++)
            for(int k=j;k<i;k++)
                vis[sg[j]^sg[k]]=i;
        sg[i]=0;
        while(vis[sg[i]]==i)sg[i]++;
    }
    int _=1;
    cin>>_;
    for(int __=1;__<=_;__++){
        int n,ans=0;cin>>n;
        for(int i=n-1;i>=0;i--){
            cin>>a[i];
            if(a[i]&1)ans^=sg[i];
        }
        if(!ans){
            cout<<"-1 -1 -1\n0\n";
            continue;
        }
        else{
            bool flag=1;
            int sum=0;
            for(int i=n-1;i>0;i--){
                if(a[i]==0)continue;//这一行写错找半天，而且不写也没关系
                for(int j=i-1;j>=0;j--)
                    for(int k=j;k>=0;k--){
                        if((ans^sg[i]^sg[j]^sg[k])==0){
                            sum++;
                            if(flag){
                                cout<<n-i-1<<" "<<n-j-1<<" "<<n-k-1<<"\n";
                                flag=0;
                            }
                        }
                    }
            }
            cout<<sum<<"\n";
        }
    }
    return 0;
}