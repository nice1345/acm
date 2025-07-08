#include<bits/stdc++.h>
using namespace std;
#define vec vector
#define vb vec<bool>
int n,c,k,id,en;
string s;
/**
 真是难在转化
 转化：所有长度为k的区间必须要有一个字母作为结尾，且s的最后一个字母必须要作为结尾
 所有长度为k的区间不存在的字母的集合及其子集都不能作为正确答案
                                                 ————高维前缀和
 枚举所有的合法集合+s的最后一个字母
 * */
void solve() {
    cin>>n>>c>>k>>s;
    en= 1<<(s[n - 1] - 'A');
    map<char,int>h;
    vb f(1<<c, false);
    for(int i=0;i<k;i++)h[s[i]]++;
    id=(1<<c)-1;
    for(auto [i,j]:h)
        id^=(1<<(i-'A'));
    f[id]=true;
    for(int i=k;i<n;i++){
        h[s[i]]++;
        h[s[i-k]]--;
        if(h[s[i-k]]==0)h.erase(s[i-k]);
        id=(1<<c)-1;
        for(auto [i,j]:h)
            id^=(1<<(i-'A'));
        f[id]= true;
    }
    for(int w=0;w<c;w++)
        for(int i=0;i<(1<<c);i++)
            if(!((i>>w)&1))
                f[i]=f[i]||f[i^(1<<w)];
    id=c;
    for(int i=1;i<(1<<c);i++)
        if(!f[i])
            id=min(id,(int)__builtin_popcount(i|en));
    cout<<id<<"\n";
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        solve();
    }
    return 0;
}

