#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define ll long long
#define pii pair<int,int>
#define vec vector
const int N = 200005;
int mod =  998244353;
/*
 枚举状态
 相邻的两个长度为k的子区间的状态转移
 当前的前k-1位是上一个的后k-1位
 int nxt=val<<1;
 if(nxt>=(1<<k))nxt-=(1<<k);
 dp[i][val]=(dp[i-1][nxt]+dp[i-1][nxt|1])%mod;
 */
void solve(){
    int n,k;
    string s;
    cin>>n>>k>>s;
    s="$"+s;
    vec<vec<int>>dp(n+5,vec<int>(1<<k,0));
    vec<bool>h(1<<k);
    function<bool(int,int)>hh=[&](int val,int len){
        for(int i=0;i<len/2;i++)
            if((val&(1<<i))>0&&(val&(1<<(len-i-1)))==0)
                return true;
            else if((val&(1<<i))==0&&(val&(1<<(len-i-1)))>0)
                return true;
        return false;
    };
    for(int i=0;i<(1<<k);i++)h[i]=hh(i,k);
    function<void(int,int)>init=[&](int val,int id){
        if(id==k+1){
            if(h[val])dp[k][val]=1;
            return;
        }
        if(s[id]=='A'||s[id]=='?')
            init(val,id+1);
        if(s[id]=='B'||s[id]=='?')
            init(val|(1<<(id-1)),id+1);
    };
    init(0,1);
    for(int i=k+1;i<=n;i++){
        function<void(int,int)>cal=[&](int val,int id){
            if(id==i+1){
                if(h[val]){
                    int nxt=val<<1;
                    if(nxt>=(1<<k))nxt-=(1<<k);
                    dp[i][val]=(dp[i-1][nxt]+dp[i-1][nxt|1])%mod;
                }
                return;
            }
            if(s[id]=='A'||s[id]=='?')
                cal(val,id+1);
            if(s[id]=='B'||s[id]=='?')
                cal(val|(1<<(id-(i-k+1))),id+1);
        };
        cal(0,i-k+1);
    }
    int ans=0;
    for(int i=0;i<(1<<k);i++)ans=(ans+dp[n][i])%mod;
    cout<<ans;
}
signed main()
{
    //freopen("D:\\CLionProject\\untitled\\r.txt","r",stdin); //输入重定向，输入数据将从r.txt文件中读取
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    //cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }


    return 0;
}

