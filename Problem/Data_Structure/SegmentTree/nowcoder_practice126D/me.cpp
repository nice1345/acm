#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define vec vector
#define pii array<int,2>
const int N = 100005;
ll mod = (ll) 998244353;
pii st[N];
int cnt=-1;
struct segmentTree{
    struct node{
        int sum=0,lazy=0,tolerance=0;
    };
    vec<node>tree;
    int len;
    segmentTree(int n){
        tree.resize(n*4+20);
        len=n;
    }
    int modify(int l,int r,int id,int ql,int qr,int val,int add){
        if(r<ql||qr<l){}
        else if(ql<=l&&r<=qr){
            tree[id].lazy+=(l-ql)*add+val;
            tree[id].tolerance+=add;
        }
        else{
            int mid=(l+r)>>1;
            tree[id].sum= modify(l,mid,(id<<1),ql,qr,val,add)+
                          modify(mid+1,r,(id<<1)+1,ql,qr,val,add);
        }
        int len=r-l+1;
        int res=tree[id].sum;
        if(tree[id].lazy!=0||tree[id].tolerance!=0)
            res+=tree[id].lazy*len+(len-1ll)*len/2ll*tree[id].tolerance;
        //  cout<<l<<" "<<r<<" "<<tree[id].sum<<" "<<tree[id].lazy<<" "<<tree[id].tolerance<<"\len";
        return res;
    }
    int query(int l,int r,int id,int ql,int qr){
        if(r<ql||qr<l)return 0;
        else if(ql<=l&&r<=qr){
            int len=r-l+1;
            int res=tree[id].sum;
            if(tree[id].lazy!=0||tree[id].tolerance!=0)
                res+=tree[id].lazy*len+(len-1ll)*len/2ll*tree[id].tolerance;
            return res;
        }
        else{
            int mid=(l+r)>>1;
            if(tree[id].lazy!=0||tree[id].tolerance!=0){
                int len=r-l+1ll;
                tree[(id<<1)].lazy+=tree[id].lazy;
                tree[(id<<1)].tolerance+=tree[id].tolerance;
                tree[(id<<1)+1].lazy+=(tree[id].lazy+(mid+1ll-l)*tree[id].tolerance);
                tree[(id<<1)+1].tolerance+=tree[id].tolerance;
                tree[id].sum+=tree[id].lazy*len+(len-1ll)*len/2ll*tree[id].tolerance;
                tree[id].lazy=0;
                tree[id].tolerance=0;
            }
            return query(l,mid,(id<<1),ql,qr)+query(mid+1,r,(id<<1)+1,ql,qr);
        }
    }
    void add(int l,int r,int val,int tt){
        modify(0,len,1,l,r,val,tt);
    }
    int get(int l,int r){
        query(0,len,1,l,r);
    }
};
void solve() {
    cnt=-1;
    int n,m;
    cin>>n;
    vec<array<int,3>>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i][0];
        while(cnt>=0&&st[cnt][0]>=a[i][0])cnt--;
        if(cnt==-1)a[i][1]=0;
        else a[i][1]=st[cnt][1]+1;
        st[++cnt]={a[i][0],i};
    }
    cnt=-1;
    vec<array<int,4>>h;
    for(int i=n-1;i>=0;i--){
        while(cnt>=0&&st[cnt][0]>=a[i][0])cnt--;
        if(cnt==-1)a[i][2]=n-1;
        else a[i][2]=st[cnt][1]-1;
        st[++cnt]={a[i][0],i};
        a[i][1]=i-a[i][1];
        a[i][2]-=i;
        if(a[i][1]>a[i][2])swap(a[i][1],a[i][2]);
        h.push_back({a[i][0],a[i][1],a[i][2],-1});
    }
    cin>>m;
    array<int,4> no;
    for(int i=0;i<m;i++){
        cin>>no[0]>>no[1]>>no[2];
        no[3]=i;
        h.push_back(no);
    }
    sort(h.begin(),h.end(),[&](array<int,4> a,array<int,4> b){
        if(a[0]==b[0])return a[3]<b[3];
        return a[0]>b[0];
    });
    segmentTree tree(n+5);
    vec<pii>pw;

    for(auto &i:h){
        // cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<" "<<i[3]<<"\len";
        if(i[3]==-1){
            //cout<<"insert-----\len";
            int l=1,r=1ll+i[1]+i[2];
          //  if(i[1]==0){
          //      tree.modify(1,len,1,1,1+i[2],1,0);
                // cout<<"-------\len";
          //  }

            //else{
                tree.modify(1,n,1,1,i[1],1,1);
                // cout<<"-------\len";
                tree.modify(1,n,1,2+i[2],1+i[1]+i[2],i[1],-1);
                // cout<<"-------\len";
                tree.modify(1,n,1,i[1]+1,1+i[2],1+i[1],0);
                //           cout<<"-------\len";
           // }
//        cout<<"insert-----end\len";
        }
        else{
//        cout<<"pw-----\len";
            pw.push_back({i[3],tree.query(1,n,1,i[1],i[2])});
//        cout<<"-------\len";
//        cout<<"pw-----end\len";

        }

    }
    sort(pw.begin(),pw.end());
    for(auto [i,j]:pw)cout<<j<<"\n";
}
signed main() {

//    freopen("D:\\CLionProject\\untitled\\r.txt","r",stdin); //输入重定向，输入数据将从r.txt文件中读取
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }


    return 0;
}
