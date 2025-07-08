#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int a[N],f[N];
int n,k,l,r,mid;
bool check1(int c){
    for(int i=1;i<=n;i++){
        if(a[i]>=c)f[i]=1;
        else f[i]=-1;
        if(i%k){
            f[i]=f[i]+f[i-1];
            if(i>k)f[i]=max(f[i],f[i-k]);
        }
        else f[i]=0;
        if(i%k==n%k&&f[i]>0)return 1;
    }
    return 0;
}
bool check0(int c){
    for(int i=1;i<=n;i++){
        if(a[i]>=c)f[i]=1;
        else f[i]=-1;
        if((i%k==0)&&f[i]+f[i-1]>0)return 1;
        if(i%k){
            f[i]=f[i]+f[i-1];
            if(i>k)f[i]=max(f[i],f[i-k]);
        }
        else f[i]=0;
    }
    return 0;
}
bool check(int c){
    if(n%k!=0)return check1(c);
    else return check0(c);
}
/**
 答案无序就无法二分了? 就不能另找单调性?
 将二分的定义改成中位数是否能大于当前的数，即是否有len/2(剩下的长度)大于当前的数
 **/
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];
        l=1,r=1e9;
        while(l<r){
            mid=(l+r+1)>>1;
            if(check(mid))l=mid;
            else r=mid-1;
        }
        cout<<l<<"\n";
    }
    return 0;
}
