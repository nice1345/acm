/**
 思路启发:https://www.cnblogs.com/luckyblock/p/18214645#e
 代码启发:tourist
 将某一列变为特殊列有n种解法
 遍历m列的n种解法
 可以花n*m找到所有解法的hash值存储到map
 再花n*m找到所有解法的贡献
 找出最大的贡献的解法
 O(nmlog(nm))
 hash底数建议随机开双哈
 因为是01性质
 此题可以用随机值异或代替hash,省去了判断某一位是0还是1,hash是加还是减
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define vec vector
const int N = 1000005;
ll mod = (ll) 998244353;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    mt19937_64 rng((ull) chrono::steady_clock::now().time_since_epoch().count());
    int T = 1;
    cin>>T;
    while (T--) {
        int h,w;cin>>h>>w;
        vec<string>s(h);
        for(string &i:s)cin>>i;
        vec<ull>val(h);
        for(ull &i:val)i=rng();
        map<ull,int>qc;
        int mh=0,mw=0,ans=0;
        vec<ull>sum(w,0);
        for(int j=0;j<w;j++){
            for(int i=0;i<h;i++)
                if(s[i][j]=='1')
                    sum[j]^=val[i];
            for(int i=0;i<h;i++)
                qc[sum[j]^val[i]]++;
        }
        for(int j=0;j<w;j++)
            for(int i=0;i<h;i++){
                int num=qc[sum[j]^val[i]];
                if(num>ans){
                    mh=i;mw=j;ans=num;
                }
            }
        cout<<ans<<"\n";
        string pw="";
        for(int i=0;i<h;i++)
            pw+=s[i][mw];
        pw[mh]=(pw[mh]=='1')?'0':'1';
        cout<<pw<<"\n";
    }
    return 0;
}
