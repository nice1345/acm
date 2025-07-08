#include <bits/stdc++.h>
#define pii pair<int,int>
#define pil pair<int,long long>
#define pli pair<long long,int>
#define vec vector
#define vii vector<int>
#define vll vector<long long>
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
const int N=5e5+5;
int ma[N],mi[N];
int al,ar,il,ir;
int a[N];
int c[N];
void solve() {
    al=il=0;ar=ir=-1;
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        c[i]=0;
    }
    c[0]=c[n+1]=0;
    int l=n-k+1;
    for(int i=1;i<l;i++){
        while (al<=ar&&a[ma[ar]]<=a[i])ar--;
        ma[++ar]=i;
        while(il<=ir&&a[mi[ir]]>=a[i])ir--;
        mi[++ir]=i;
    }
    int mx=INT_MAX;
    for(int i=l;i<=n;i++){
        while (al<=ar&&a[ma[ar]]<=a[i])ar--;
        ma[++ar]=i;
        while(il<=ir&&a[mi[ir]]>=a[i])ir--;
        mi[++ir]=i;
        while (al<=ar&&ma[al]<(i-l+1))al++;
        while (il<=ir&&mi[il]<(i-l+1))il++;
        mx=min(mx,(a[ma[al]]-a[mi[il]]));
    }
    al=il=0;ar=ir=0;
    ma[0]=1;mi[0]=1;
    for(int i=1,j=1;i<=n;i++){
        while(al<=ar&&ma[al]<i)al++;
        while(il<=ir&&mi[il]<i)il++;
        while(mx>(a[ma[al]]-a[mi[il]])&&++j<=n){
            while (al<=ar&&a[ma[ar]]<=a[j])ar--;
            ma[++ar]=j;
            while(il<=ir&&a[mi[ir]]>=a[j])ir--;
            mi[++ir]=j;
        }
        if(mx>(a[ma[al]]-a[mi[il]]))break;
        c[j-i+1]++;c[n-i+2]--;
    }
    int ans=0;
    for(int i=1;i<=l;i++){
        ans+=c[i];
        if(ans>=k){
            cout<<mx<<" "<<i<<"\n";
            return;
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(10);
    int T=1;
    cin>>T;
    for(int _=1;_<=T;_++){
        solve();
    }
    return 0;
}