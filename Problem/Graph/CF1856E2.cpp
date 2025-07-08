//博客:https://www.luogu.com.cn/blog/502410/muti-bag-on-tree-cf1856e2
//将出现的次数为偶数的减出来,剩下的数种类不同,最多sqrt(len)个数将背包优化为sqrt(len),
//背包可以用bitset()优化,只剩下遍历的问题
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
using ll=long long;
int T,n,m,f[N],sz[N],lc[N],open[N];
vector<int>lk[N];
bitset<N>dp;
ll ans;
int main(){
    ios::sync_with_stdio(false);
    int i,j,k,r,x;
    cin>>n;
    for(x=2;x<=n;++x)cin>>f[x],lk[f[x]].push_back(x);
    for(x=n;x;--x){
        ++sz[x];
        if(f[x]){
            sz[f[x]]+=sz[x];
            if(sz[lc[f[x]]]<sz[x])lc[f[x]]=x;
        }
    }
    for(x=1;x<=n;++x){
        if(sz[x]>1){
            if(sz[lc[x]]*2>=sz[x]-1)ans+=ll(sz[lc[x]])*(sz[x]-sz[lc[x]]-1);
            else{
                for(i=1;i<=sz[x];++i)open[i]= dp[i]=0;
                for(int y:lk[x])++open[sz[y]];dp[0]=1;
                for(k=1;k<=sz[x];++k){
                    if(open[k]){
                        for(i=0;i<k;++i){
                            for(j=0,r=-1e9;j*k+i<=sz[x];++j){
                                if(dp[j*k+i])r=j;
                                else if(j-r <= open[k])dp[j * k + i]=1;
                            }
                        }
                    }
                }
                for(k=sz[x]-1>>1;!dp[k];--k);
                ans+=ll(sz[x]-1-k)*k;
            }
        }
    }

    printf("%lld\n",ans);
    return 0;
}