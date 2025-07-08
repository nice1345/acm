//题解:https://zhuanlan.zhihu.com/p/695083555
//官方题解更易懂
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ll long long
#define pii pair<int,int>
#define vec vector
const int N=200005;
const int mod=998244353;
int hm(int a){
    int res=-1;
    while(a){
        res++;
        a>>=1;
    }
    return res;
}
int main( )
{
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while (_--){
        int n,k;
        cin>>n>>k;
        int hk=hm(k);
        vec<int>pw;
        if(k!=1){
            int po=1;
            for(int i=1;i<hk;i++){po<<=1;pw.push_back(po);}
            po<<=1;
            if(k>po)
                pw.push_back(k-po);
            pw.push_back(k+1);
//    po=pow(2,hk+1);
//    pw.push_back(k+k+1);
//    for(int i=hk+2;i<=21;i++){po<<=1;pw.push_back(po);}
//    pw.push_back(1);
            po=k+k;
            while(po<=n){pw.push_back(po);po*=2;}
            if(k*3<=n)pw.push_back(k*3);
            pw.push_back(1);
        }
        else{
            hk=hm(n);
            int po=1;
            for(int i=1;i<=hk;i++){po<<=1;pw.push_back(po);}
            pw.push_back(3);
        }
        cout<<pw.size()<<"\n";
        for(int i:pw)cout<<i<<" ";
        cout<<"\n";
    }
    return 0;
}