#include<bits/stdc++.h>
using namespace std;
#define vec vector
int x;
/**
 吐了，有这样搞诈骗的
 说到底还是思维弱了
 题解说最优方法指的是每棵树删除叶子节点到理想位置，每棵树只贡献一颗子树
 证明
 将树拆成n各部分，n个部分或起来一定<=n,
 拆成n各部分不如通过删除叶子节点直到树的大小等于n个部分或起来的值
 所以不如只保留一个部分

 那题意就转化为每个树的大小该咋减小使得整体或起来最大，贪心即可
 * */
void solve() {
    int k;cin>>k;
    vec<int>sz(k);
    for(int &i:sz){
        cin>>i;
        for(int j=1;j<i;j++)cin>>x;
    }
    sort(sz.rbegin(),sz.rend());
    int ans=0;
    for(int i=21;i>=0;i--){
        x=0;
        for(int j:sz)
            if(j>>i&1)x++;
        if(x>1){
            ans|=(1<<i+1)-1;
            break;
        }
        if(x==1)ans|=1<<i;
    }
    cout<<ans<<"\n";
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

