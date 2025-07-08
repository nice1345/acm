#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
//题解：https://www.cnblogs.com/luckyblock/p/18353021#e1
int n,cnt,_,f,c;
long long a[N],arr[N];
int ls[N],rs[N],st[N],fa[N],sz[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y)return;
    fa[x]=y;sz[y]+=sz[x];
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>_;
    while(_--){
        cin>>n>>cnt;
        cnt=0;
        ls[0]=rs[0]=arr[0]=0;sz[0]=1;
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
            ls[i]=rs[i]=0;
            cin>>a[i];
            arr[i]= a[i] + arr[i - 1];
            while(cnt!=0&&a[i]>a[st[cnt]])cnt--;
            ls[i]=rs[st[cnt]];
            rs[st[cnt]]=i;
            if(ls[i]&&arr[i-1]-arr[st[cnt]]>=a[i])merge(ls[i],i);
            st[++cnt]=i;
            f=find(st[1]);c=rs[f];
            while(c){
                if (arr[i] - arr[f] >= a[f]) merge(f, c);
                f = find(c), c = rs[f];
            }
            cout<<sz[find(st[1])]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
