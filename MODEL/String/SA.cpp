#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=100005;
char s[N],rk[N],tmp[N],sa[N];
int n,k=0;

bool cmp_sa(int a,int b){
    if(rk[a]!=rk[b])return rk[a]<rk[b];
    else {
        int ra=a+k<n?rk[a+k]:-1;
        int rb=b+k<n?rk[b+k]:-1;
        return ra<rb;
    }
}

void calc_sa(){
    for(int i=0;i<n;i++){
        rk[i]=s[i];
        sa[i]=i;
    }
    for(k=1;k<=n;k<<=1){
        sort(sa,sa+n,cmp_sa);
        tmp[sa[0]]=0;
        //根据以前的排名和sa推出现在的rk
        for(int i=1;i<n;i++)
            tmp[sa[i]]=tmp[sa[i-1]]+ cmp_sa(sa[i],sa[i-1])?1:0;
        //更新排名
        memccpy(rk,tmp,n,0);
    }
}
int main(){
    scanf("%s",s);
    n= strlen(s);
    calc_sa();
    for(int i=0;i<n;i++){
        printf("%d ",sa[i]);
    }
    return 0;
}