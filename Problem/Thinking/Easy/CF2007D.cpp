#include<bits/stdc++.h>
using namespace std;
/**
 * 01串的回文首尾必定相同
 * 此题路径不一定是回文
 * 把连续的0或1看成单独的之后必定是回文
 * */
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        int n;cin>>n;
        vector<int>d(n+1,0);
        for(int i=1;i<n;i++){
            int u,v;cin>>u>>v;
            d[u]++;d[v]++;
        }
        int root;
        string s;cin>>s;s="#"+s;
        int zero=0,one=0,q=0,w=0;
        for(int i=2;i<=n;i++)
            if(d[i]==1){
                if(s[i]=='0')one++;
                else if(s[i]=='1')zero++;
                else q++;
            }
            else if(s[i]=='?')w++;
        if(s[1]=='1')cout<<one+(q+1)/2<<"\n";
        else if(s[1]=='0')cout<<zero+(q+1)/2<<"\n";
        else{
            if(zero>one)cout<<zero+q/2<<"\n";
            else if(one>zero)cout<<one+q/2<<"\n";
            else{
                if(w&1)cout<<one+(q+1)/2<<"\n";
                else cout<<one+q/2<<"\n";
            }
        }
    }
    return 0;
}