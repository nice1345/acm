//题解：https://zhuanlan.zhihu.com/p/695439222
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define vec vector
#define pii array<int,2>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
//https://zhuanlan.zhihu.com/p/695354439
int n;
struct ScanLine_Tree{
    vec<array<int,2>>tree;
    void build(int l,int r,int id){
        tree[id][0]=0;
        tree[id][1]=r;
        if(l!=r){
            int mid=(l+r)>>1;
            build(l,mid,id*2+1);
            build(mid+1,r,id*2+2);
        }
    }
    //初始化0~n的线段树
    ScanLine_Tree(int n){
        tree.resize(n*4+5);
        build(0,n,0);
    }
    void moify(int nl,int nr,int ql,int qr,int id,int tmp){
        if(nr<ql||qr<nl)return;
        if(ql<=nl&&nr<=qr)
            tree[id][0]+=tmp;
        else{
            int mid=(nl+nr)>>1;
            moify(nl, mid, ql, qr,(id<<1)+1,tmp);
            moify(mid+1,nr, ql, qr,(id<<1)+2,tmp);
        }
        if(tree[id][0])tree[id][1]=-1;
        else
        if(nl==nr)tree[id][1]=nr;
        else
            tree[id][1]=max(tree[(id<<1)+1][1],tree[(id<<1)+2][1]);
    }
    int query(int nl,int nr,int ql,int qr,int id){
        if(nr<ql||qr<nl)return -1;
        if(ql<=nl&&nr<=qr)
            return tree[id][1];
        else{
            int mid=(nl+nr)>>1;
            return max(query(nl, mid, ql, qr,(id<<1)+1),query(mid+1,nr, ql, qr,(id<<1)+2));
        }
    }
};
void solve(){
    cin>>n;
    vec<int>a(n),pre(n);
    unordered_map<int,int>pr,su;
    for(int &i:a)cin>>i;
    for(int i=0;i<n;i++){
        if(!pr.count(a[i]))pre[i]=0;
        else pre[i]=pr[a[i]]+1;
        pr[a[i]]=i;
    }
    int suf;
    vec<vec<pii>>add(n),sub(n+1);
    for(int i=n-1;i>=0;i--){
        if(!su.count(a[i]))suf=n-1;
        else suf=su[a[i]]-1;
        su[a[i]]=i;
        add[i].push_back({pre[i],i});
        sub[suf+1].push_back({pre[i],i});
    }
    vec<int>q(n,n+1);
    ScanLine_Tree tree(n);
    int l,ans=0;
    for(int i=0;i<n;i++){
        for(pii seg:add[i])tree.moify(0,n,seg[0],seg[1],0,1);
        for(pii seg:sub[i])tree.moify(0,n,seg[0],seg[1],0,-1);
        l=tree.query(0,n,0,i,0);
        if(l!=-1)q[l]=min(q[l],i);
    }
    l=n+1;
    for(int i=n-1;i>=0;i--){
        if(q[i]<l){
            l=i;
            ans++;
        }
    }
    cout<<ans<<"\n";
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    cin>>T;
    while (T--) {
        solve();
    }
    return 0;
}


/** 109ms神奇代码  */
//#pragma GCC optimize(2)
//#include<bits/stdc++.h>
//#define ll long long
//#define sz(a) ((int)(a).size())
//#define For(i, a, len) for(int i = a; i <= len; i++)
//#define rof(i, len, a) for(int i = len; i >= a; i--)
//#define endl "\len"
//using namespace std;
//const int maxn = 3e5 + 5;
//int T;
//int len, a[maxn], cnt, sum;
//void solve()
//{
//    cin >> len;
//    vector<int> nxt(len + 5), pre(len + 5), lst(len + 5);
//    vector<pair<int, int> > q(len + 5);
//    For(i, 1, len)
//    {
//        cin >> a[i];
//        pre[i] = lst[a[i]];
//        nxt[lst[a[i]]] = i;
//        lst[a[i]] = i;
//    }
//    For(i, 1, len) nxt[lst[a[i]]] = len + 1;
//    cnt = 0;
//    sum = 0;
//    q[++cnt] = {0, len + 1};
//    rof(i, len, 1)
//    {
//        int res = q[cnt].second;
//        if(nxt[i] < res)
//        {
//            sum++;
//            cnt = 1;
//            q[cnt] = {0, i};
//        }
//        else
//        {
//            while(cnt > 1 && nxt[i] >= q[cnt - 1].second && pre[i] < q[cnt].first) cnt--;
//            cnt++;
//            q[cnt] = {max(pre[i] + 1, q[cnt - 1].first), i};
//        }
//        while(q[cnt].first == i) cnt--;
//    }
//    cout << sum << endl;
//    return;
//}
//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
//    cin >> T;
//    //T = 1;
//    For(I, 1, T)
//    {
//        solve();
//    }
//    return 0;
//}