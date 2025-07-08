
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
 int tree[N];
 long lowbit(int a){return a&(-a);}

 void add(int a,int c){
    for(int i=a;i<=N;i+=lowbit(i))tree[i]+=c;
}
 int sum(int a){
    int ans=0;
    for(int i=a;i>0;i-=lowbit(i))ans+=tree[i];
    return ans;
}
template<typename T>
struct BIT{
    int len;
    vector<T>tree;
    BIT(int n){
        tree.resize(n);
        len=n;
    }
    void add(int i,T v){for(;i<len;i+=i&-i)tree[i]+=v;}
    T query(int i){T res=0;for(;i;i-=i&-i)res+=tree[i];return res;}
};
/**
 树状数组上使用逼近法
 详情见这发提交：https://codeforces.com/contest/1997/submission/277860809
 题解博客：https://www.cnblogs.com/zsc985246/p/18333684
 * */

int main() {


    return 0;
}
