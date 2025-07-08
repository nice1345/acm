#include<bits/stdc++.h>
using namespace std;
#define vec vector
#define gg(nn) vec<basic_string<int>>g(nn+1,basic_string<int>());
/**
 dfs生成树判奇环
 在生成树中
 分成深度为奇数的点和偶数的点

 怎样才能离线分配呢
     a
   ab    ac
 b     bc    c
 ab 为 Alice 给出 a  b 的次数
 ab  bc  ac  可以只选ab
  奇数的点染为a  偶数的点染为b
  奇数的点  染完了就把另一个颜色分给偶数点
  偶数的点同理
 * */
void solve() {
    int n,m;cin>>n>>m;
    gg(n)
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        g[u]+=v;g[v]+=u;
    }
    vec<int>d(n+1);
    bool flag=0;
    function<void(int)>dfs=[&](int no){
        for(int so:g[no]){
            if(d[so]){
                if((d[no]-d[so])%2==0)flag=1;
                continue;
            }
            d[so]=d[no]+1;
            dfs(so);
        }
    };
    d[1]=1;dfs(1);
    if(flag){
        cout<<"Alice"<<endl;
        int ne;
        for(int i=0;i<n;i++){
            cout<<"1 2"<<endl;
            cin>>ne;cin>>ne;
        }
    }
    else{
        cout<<"Bob"<<endl;
        vec<int>q1,q2;
        for(int i=1;i<=n;i++)
            if(d[i]&1)q1.emplace_back(i);
            else q2.emplace_back(i);
        int a,b;
        for(int i=0;i<n;i++){
            cin>>a>>b;
            if(a>b)swap(a,b);
            if(a==1){
                if(q1.size()){
                    cout<<q1.back()<<" 1"<<endl;
                    q1.pop_back();
                }
                else{
                    cout<<q2.back()<<" "<<b<<endl;
                    q2.pop_back();
                }
            }
            else{
                if(q2.size()){
                    cout<<q2.back()<<" 2"<<endl;
                    q2.pop_back();
                }
                else{
                    cout<<q1.back()<<" "<<b<<endl;
                    q1.pop_back();
                }
            }
        }
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}