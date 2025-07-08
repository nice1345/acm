#include<bits/stdc++.h>
using namespace std;
//题目链接：https://codeforces.com/gym/546939/problem/C
//题解：https://zhuanlan.zhihu.com/p/565553750
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    string s;cin>>s;
    s='@'+s;
    vector<int> dp(n+1,0);
    if(s[1]=='1')dp[1]=1;
    for(int i=2;i<=n;i++){
        if(s[i]=='1')dp[i]=max(dp[i-1],dp[i-2]+1);
        else dp[i]=dp[i-1];
    }
    int pre=0;
    vector<int> f1(n+1,-1),f2(n+1,-1);
    while(pre<=n&&s[pre]!='1')pre++;
    while(pre<=n){
        int suf=pre;
        while(suf<=n&&s[suf]=='1'){
            f2[suf]=pre;suf++;
        }
        pre=suf;
        while(pre<=n&&s[pre]!='1')pre++;
    }
    pre=n;
    while(pre>0&&s[pre]!='1')pre--;
    while(pre>0){
        int suf=pre;
        while(suf>0&&s[suf]=='1'){
            f1[suf]=pre;
            suf--;
        }
        pre=suf;
        while(pre>0&&s[pre]!='1')pre--;
    }
    while(m--){
        int l,r;cin>>l>>r;
        int sum=0;
        if(r-l==2){
            if(s[l]=='1')sum=1;
            if(s[l+1]=='1')sum=1;
            if(s[l+2]=='1')sum=1;
            if(sum)cout<<"0\n";
            else cout<<"1\n";
        }
        else{
            if(f1[l]>=r)cout<<"0\n";
            else{
                int sum=0;
                int q=f1[l],w=f2[r];
                if(q==-1)q=l;
                else sum+=q-l+1,q++;
                if(w==-1)w=r;
                else w--,sum+=r-w;
                sum=(sum+1)>>1;
                sum+=dp[w]-dp[q-1];
                cout<<max(0,(r-l+1)/3-sum)<<'\n';
            }
        }
    }
    return 0;
}