//题目链接:https://ac.nowcoder.com/acm/contest/57361/I
/**
 首先，观察范围，可以按照将字符串分成两类：
小于等于20,暴力枚举符合条件的字符串进行统计。
大于20,这种字符串最多有20个，用容斥技巧处理;
2. 解决细节
直接举字符串的选择情况：
枚举出选择情况之后，很容易就能计算出它们能够共同表达的字符串集合：
一个位置上可以匹配： 贡献一：
一个位置上全为'?' ： 当前匹配的前缀总数乘上2：
一个位置上不同 ： 匹配串为0

容斥原理
只选择一个:+
选择两个,得到的必然是1步骤中贡献的交集:-
选择三个,得到的结果，对应2步骤中结果的交集:+
... 奇数则贡献， 偶数则减去：
高维前缀和
包含的字符串越多,所表示的字符串越少;
则子集就是包含了现有的字符串的情况下又包含了别的字符串
可用高维前缀和父集减子集求出每一种情况的精确数量
 * */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 400;
ll mod = (ll) 998244353;

ll pow2[405];
vector<string>s[401];
string ns[400];

ll Bigsolve(int le){
    int sum=s[le].size();
    int mx=(1<<sum);
    string base="";
    for(int j=0;j<le;j++)base+="?";
    vector<ll>dp(mx);
    //全0方案不能进行这样判断
    for(int i=1;i<mx;i++){//遍历选择方案
        string no=base;
        bool flag= true;
        for(int w=0;w<sum&&flag;w++){//遍历第w个字符串有没有选
            if((i>>w)&1){
                for(int j=0;j<le;j++){
                    if(s[le][w][j]!='?'){
                        if(no[j]=='?')no[j]=s[le][w][j];
                        else if(no[j]!=s[le][w][j]){
                            flag= false;
                            break;
                        }
                    }
                }
            }
        }
        if(flag) dp[i]=pow2[count(no.begin(),no.end(),'?')];
    }
ll ans=0;
    //方法一:直接容斥(类比欧拉函数推导)
//    for(int i=1;i<mx;i++){
//        int b=__builtin_popcount(i);
//        if((b%2))ans=(ans+dp[i])%mod;
//        else ans=(ans-dp[i]+mod)%mod;
//    }
//    return ans;

//千万注意子集关系别搞反了
    //方法二:高维前缀和容斥
    for(int w=0;w<sum;w++){
        for(int i=0;i<mx;i++){
            if((i>>w)&1)dp[i^(1<<w)]=(dp[i^(1<<w)]-dp[i]+mod)%mod;
        }
    }
    for(int i=1;i<mx;i++)ans=(ans+dp[i])%mod;
    return ans;
}

ll Smallsolve(int le){
    int mx=(1<<le);
    ll ans=0;
    for(int i=0;i<mx;i++){
        for(string j:s[le]){
            bool flag = true;
            for(int k=0;k<le;k++){
                if(j[k]=='?')continue;
                if(j[k]!=('0'+((i>>k)&1))){
                    flag= false;
                    break;
                }
            }
            if(flag){
                ans++;
                break;
            }
        }
    }
    return ans;
}

int main() {
    /**
 string s;
 count(s.begin(),s.end(),'?')统计字符串中?的数量
 **/
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    pow2[0]=1;
for(int i=1;i<=N;i++){
    pow2[i]=pow2[i-1]*(ll)2%mod;
}

int n,len;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>ns[i];
        len=ns[i].size();
        s[len].push_back(ns[i]);
    }

    ll pw=0;
    for(int i=1;i<=400;i++){
        if(s[i].size()==0)continue;
        if(i>20)pw=(pw+Bigsolve(i))%mod;
        else pw=(pw+ Smallsolve(i))%mod;
    }
    cout<<pw<<endl;
    return 0;
}
