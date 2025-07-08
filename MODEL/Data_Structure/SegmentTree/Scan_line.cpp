#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
#define vec vector
struct seg{
    int x,y1,y2,v;
};
struct node{
    int cnt=0;//覆盖次数
    int val=0;//贡献值
    int l,r;//节点范围
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    int x1,x2,y1,y2;
    int mx=1000000;
    vec<int>w;
    vec<seg>h;
    for(int i=0;i<n;i++){
        cin>>x1>>y1>>x2>>y2;
        h.push_back({x1,y1,y2,1});
        h.push_back({x2,y1,y2,-1});
        w.push_back(y1);w.push_back(y2);
        mx=min(mx,x1);
    }
    sort(w.begin(),w.end());
    w.erase(unique(w.begin(),w.end()),w.end());
    sort(h.begin(),h.end(),[&](seg a,seg b){
        return a.x<b.x;
    });
    int size=(int)w.size()-1;
    vec<node>tree(size*16+5);
    vec<bool>is(size*16+5,0);
    function<void(int,int,int)>build=[&](int il,int ir,int id){
        auto &[cnt,val,l,r]=tree[id];
        if(il==ir){
            l=w[il];r=w[il+1];is[id]=1;
        }
        else{
            int mid=(il+ir)>>1;
            build(il,mid,id<<1);
            build(mid+1,ir,(id<<1)+1);
            l=tree[id<<1].l;
            r=tree[(id<<1)+1].r;
        }
        // cout<<cnt<<" "<<val<<" "<<l<<" "<<r<<" "<<idx<<"\len";
    };
    build(0,size-1,1);
    function<void(int)>update=[&](int id){
        auto &[cnt,val,l,r]=tree[id];
        if(cnt==0){
            if(is[id])val=0;
            else tree[id<<1].val+tree[(id<<1)+1].val;
        }
        else val=r-l;
    };
    function<void(int,int,int,int)>moify=[&](int ml,int mr,int id,int v){
        auto &[cnt,val,l,r]=tree[id];
        if(cnt>0)val=r-l;
        if(r<=ml||mr<=l)return ;
        else if(ml<=l&&r<=mr){
            if(v==1){
                cnt++;val=r-l;
            }
            else{
                cnt--;
                if(cnt)val=r-l;
                else{
                    if(is[id])val=0;
                    else
                        val=tree[(id<<1)].val+tree[(id<<1)+1].val;
                }
            }
        }
        else if(!is[id]){
            moify(ml,mr,(id<<1),v);
            moify(ml,mr,(id<<1)+1,v);
            if(cnt)val=r-l;
            else
                val=tree[(id<<1)].val+tree[(id<<1)+1].val;
        }
    };
    int last=mx,now=mx;
    ll ans=0;
    for(int i=0;i<h.size();i++){
        auto  &[x,l,r,v]=h[i];
        if(now!=x){
            last=now;
            now=x;
            ans+=(ll)(now-last)*(ll)tree[1].val;
        }
        moify(l,r,1,v);
    }
    cout<<ans<<"\n";
    return 0;
}
