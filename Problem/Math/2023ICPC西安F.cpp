//题目链接:https://codeforces.com/gym/476283/problem/F

#pragma GCC optimize(3)
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
#define ll long long
#define ull unsigned long long
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
const int _G=3,MOD=998244353,N=3e5+10,M=5010;

int p=0,x=0,k=0,g=0,indx=0;

int qpow(int a,int t=MOD-2,int mod=MOD){
    int ans=1;
    while(t){
        if(t&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;t>>=1;
    }return ans;
}
const int invG=qpow(_G);
int tr[N<<1],tf;
void tpre(int n){
    if (tf==n)return;
    tf=n;
    for(int i=0;i<n;i++)
        tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
}
void NTT(int *g,bool op,int n)
{
    tpre(n);
    static ull f[N<<1],w[N<<1]={1};
    for (int i=0;i<n;i++)f[i]=(((ll)MOD<<5)+g[tr[i]])%MOD;
    for(int l=1;l<n;l<<=1){
        ull tG=qpow(op?_G:invG,(MOD-1)/(l+l));
        for (int i=1;i<l;i++)w[i]=w[i-1]*tG%MOD;
        for(int k=0;k<n;k+=l+l)
            for(int p=0;p<l;p++){
                int tt=w[p]*f[k|l|p]%MOD;
                f[k|l|p]=f[k|p]+MOD-tt;
                f[k|p]+=tt;
            }
        if (l==(1<<10))
            for (int i=0;i<n;i++)f[i]%=MOD;
    }if (!op){
        ull invn=qpow(n);
        for(int i=0;i<n;++i)
            g[i]=f[i]%MOD*invn%MOD;
    }else for(int i=0;i<n;++i)g[i]=f[i]%MOD;
}
void px(int *f,int *g,int n)
{for(int i=0;i<n;++i)f[i]=1ll*f[i]*g[i]%MOD;}
void times(int *f,int *g,int len,int lim)
{
    static int sav[N<<1];
    static int n=1;for(n=1;n<len+len;n<<=1);
    cpy(sav,g,n);
    NTT(f,1,n);NTT(sav,1,n);
    px(f,sav,n);NTT(f,0,n);
    for(int i=p-1;i<(p-1)<<1;++i){
        f[i%(p-1)]=(f[i]+f[i%(p-1)])%MOD;
        f[i]=0;
    }
    clr(f+lim,n-lim);
}

int getG(int m){
    static vector<int> che;
    che.clear();
    if(m==2){
        return 1;
    }
    int temp=m-1;
    for(int i=2;1ll*i*i<=temp;++i){
        if(temp%i==0){
            che.push_back((m-1)/i);
            while(temp%i==0)temp/=i;
        }
    }
    if(temp>1)che.push_back((m-1)/temp);

    for(int i=2;;++i){
        if(__gcd(i,m)!=1)continue;
        bool flag=true;
        for(int j:che){
            if(qpow(i,j,m)==1){
                flag=false;
                break;
            }
        }
        if(flag){
            return i;
        }
    }
}

string s;

int fac[M],invfac[M],ind[M],B[N],A[N];
void ini(){
    fac[0]=1;
    for(int i=1;i<p;++i)fac[i]=1ll*fac[i-1]*i%p;
    invfac[p-1]=qpow(fac[p-1],p-2,p);
    for(int i=p-2;i>=0;--i)invfac[i]=1ll*invfac[i+1]*(i+1)%p;
    for(int i=1;i<p;++i){
        int now=1;
        for(int j=0;j<p-1;++j){
            if(now==i){
                ind[i]=j;
                break;
            }
            now=1ll*now*g%p;
        }
    }
    indx=ind[x];
}

int C(int n,int m,int mod){
    if(m>n)return 0;
    return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

void solve(){
    cin>>s>>p>>x;
    g=getG(p);
    ini();
    for(int i=0;i<p;++i){
        for(int j=0;j<=i;++j){
            B[ind[C(i,j,p)]]++;
        }
    }
    A[0]=1;
    int pos=s.length()-1;
    while(pos>=0){
        if(s[pos]=='1'){
            times(A,B,p,p);
        }
        times(B,B,p,p);
        pos--;
    }
    cout<<(A[indx])%MOD<<"\n";
}

signed main(){
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T=1;
    while(T--)solve();
    return 0;
}