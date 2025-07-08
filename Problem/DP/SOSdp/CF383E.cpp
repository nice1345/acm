
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = (1<<24);
ll mod = (ll) 998244353;
ll dp[N+5];
char s[3];
int main() {
int n;
    scanf("%d",&n);


    for(int i=0;i<n;i++){
        int sum=0;
        scanf("%s",s);
        for(int j=0;j<3;j++)
            if(s[j]<='x')sum|=(1<<(s[j]-'a'));
        dp[sum]++;
    }


    for(int w=0;w<24;w++){
        for(int i=0;i<N;i++){
            if((i>>w)&1)dp[i]+=dp[i^(1<<w)];
        }
    }


    int ans=0;
    for(int i=0;i<N;i++){
        ans^=((n-dp[i])*(n-dp[i]));
    }
    printf("%d\n",ans);
    return 0;
}
