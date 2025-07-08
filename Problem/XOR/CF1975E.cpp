#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
/**
 树上链问题咋就没想到树刨呢
 但仔细想想还有可以简化
 只要拥有2个子黑节点的黑点只有一个且该点父节点为白点或没有，(核心)
 且其他黑点最多只有一个子黑点，必为链
 此题用异或处理2个子黑节点的黑点状态，当有2个子黑节点的黑点只有一个，所有两个子黑节点的黑点的异或和就是剩下的那个点，省去了lod的复杂度
 * */
int f[N];
vector<int> g[N];
int col[N],num[N];
int faw,sum_two,sum_more,tot_black,xor_two;
int n;
void init(){
    sum_two=0;
    tot_black=0;
    sum_more=0;
    faw=0;
    xor_two=0;
    for(int i=1;i<=n;i++){
        g[i].clear();
        num[i]=0;
    }
}

void dfs(int x,int fa){
    f[x]=fa;
    if(col[x]==1)tot_black++;
    int sum=0;
    for(auto i:g[x]){
        if(i==fa)continue;
        dfs(i,x);
        if(col[i]==1)sum++;
    }
    if(col[fa]==0&&col[x]==1)faw++;
    if(col[x]==1){
        if(sum==2)sum_two++,xor_two^=x;
        if(sum>2)sum_more++;
    }
    num[x]=sum;
}

void flip(int x){
    col[x]^=1;
    int d = col[x]==1?1:-1;
    tot_black+=d;
    if(col[f[x]]==0)faw+=d;
    if(num[x]==2)sum_two+=d,xor_two^=x;
    if(num[x]>2)sum_more+=d;
    faw-=d*num[x];
    if(col[x]==1){
        if(col[f[x]]==1&&num[f[x]]==2)sum_two--,sum_more++,xor_two^=f[x];
        num[f[x]]++;
        if(col[f[x]]==1&&num[f[x]]==2)sum_two++,xor_two^=f[x];
    }else{
        if(col[f[x]]==1&&num[f[x]]==2)sum_two--,xor_two^=f[x];
        num[f[x]]--;
        if(col[f[x]]==1&&num[f[x]]==2){
            sum_two++;
            sum_more--;
            xor_two^=f[x];
        }
    }
}

bool check(){
    if(!tot_black)return false;
    if(sum_more||sum_two>1)return false;
    if(faw>1)return false;
    if(sum_two&&col[f[xor_two]]==1)return false;
    return true;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        init();
        int q;
        scanf("%d %d",&n,&q);
        for(int i=1;i<=n;i++) cin>>col[i];
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1,0);
        while(q--){
            int x;
            scanf("%d",&x);
            flip(x);
            if(check()) printf("Yes\n");
            else printf("No\n");
        }
    }
}