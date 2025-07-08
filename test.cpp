
 #include <bits/stdc++.h>
// #define int long long
 typedef long long ll;
 using namespace std;
const int  N=(int)1e7+5;
int gcd(int a,int b){
//    if(sum==0)return tree;
//    return gcd(sum,tree%sum);
    while(b^=a^=b^=a%=b);
    return a;
  //  return sum?gcd(sum,tree%sum):tree;
}

 int getRand(int min, int max) {
     return (rand() % (max - min + 1)) + min;
 }
#define vec vector
#define pii pair<int,int>
 vec<pii>g[N];
 int sum[N];
 ll dis[N];
 int n,u,v,w;
 void dfs(int no,int fa){
     sum[no]++;
     for(auto [i,j]:g[no]){
         if(i==fa)continue;
         dfs(i,no);
         sum[no]+=sum[i];
         dis[no]+=(ll)sum[i]*j+dis[i];
     }
 }
 void dfs1(int no,int fa){
     for(auto [i,j]:g[no]){
         if(i==fa)continue;
         dis[i]=(ll)(n-sum[i]*2)*(ll)j+dis[no];
         dfs1(i,no);
     }
 }
 signed main() {
     cin.tie(0)->sync_with_stdio(0);
    freopen("8.in", "r", stdin); //设置 cin scanf 这些输入流都从 test01.in
    freopen("8.out", "w", stdout); //设置 cout printf 这些输出流都输出到 test01.out里面去
     cin>>n;
     for(int i=1;i<n;i++){
         cin>>u>>v>>w;
         g[u].push_back({v,w});
         g[v].push_back({u,w});
     }
     dfs(1,0);
     dfs1(1,0);
     for(int i=1;i<n;i++)cout<<dis[i]<<" ";
     cout<<dis[n];




//     freopen("D:\Dev\CLionProject\untitled\w.txt", "w", stdout); //设置 cout printf 这些输出流都输出到 test01.out里面去
//    //下面读入数据，写标程代码，以输出十个数和为例
//    int len=10000000;
//    cout<<len<<endl;
//     srand((unsigned)time(NULL));
//     for(int i=2;i<=len;i++){
//         int u=rand()%(i-1)+1,w=rand()%(10000);
//         cout<<u<<" "<<i<<" "<<w<<endl;
//     }
//     cout<<endl;


     return 0;
 }


