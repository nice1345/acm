/**
 题目链接；https://codeforces.com/contest/1973/problem/D
 题解：https://zhuanlan.zhihu.com/p/698402487
 n次找到最大值ma，m一定为ma的倍数，k部分最小的一部分一定<=n/k,m<=n/k*ma
 又m一定为ma的倍数，m一定为ma,2*ma,3*ma,....,n/k*ma
 枚举1到n/k次，每次不超过k次
 总次数n+n/k*k<=n*2
 * */
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
const int N=200005;
const int mod=998244353;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        int n,k;cin>>n>>k;
        int ma=1,ne;
        for(int i=n;i>1;i--){
            cout<<"? 1 "<<i*n<<endl;
            cin>>ne;
            if(ne==n){
                ma=i;
                break;
            }
        }
        int sum,l;
        int ans=-1;
        for(int i=n/k;i>0;i--){
            l=1;sum=0;
            while(l<=n&&sum<k){
                cout<<"? "<<l<<" "<<i*ma<<endl;
                cin>>l;
                l++;
                sum++;
            }
            if(l==n+1&&sum==k){
                ans=i*ma;
                break;
            }
        }
        cout<<"! "<<ans<<endl;
        int flag;
        cin>>flag;
    }
    return 0;
}

