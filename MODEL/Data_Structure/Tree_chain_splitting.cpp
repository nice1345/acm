
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
//ll mod = (ll) 998244353;
//P3379
//写的什么**玩意,看看人家的 https://www.luogu.com.cn/record/142802921
template<typename T>
struct seg_tree{
    int len,cnt=0,root;
    vector<int>last,go,now,son_num,new_idx,top,deep,weight_son,idx,f;
    vector<T>tree,lazy,w;
    T m;
public:
    seg_tree(int le,int ro,T mm,vector<T>val){
        len=le;root=ro;m=mm;
        for(int i=0;i<len+5;i++){
           last.push_back(0);last.push_back(0);
           go.push_back(0);go.push_back(0);now.push_back(0);
           top.push_back(0);new_idx.push_back(0);
           son_num.push_back(0);deep.push_back(0);
           weight_son.push_back(0);son_num.push_back(0);
           idx.push_back(0);
           f.push_back(0);
           for(int j=0;j<8;j++){
               tree.push_back(0);lazy.push_back(0);
           }
           if(i>=1&&i<=len)w.push_back(val[i]);
           else w.push_back(0);
        }
    }
    void add(int u,int v){
        last[++cnt]=now[u];
        go[cnt]=v;
        now[u]=cnt;
    }
    void dfs1(int no,int fa,int de){
        deep[no]=de;f[no]=fa;
         son_num[no]=1;int ma_num=0;
        int so;
        for(int i=now[no];i;i=last[i]){
           so=go[i];
            if(so==fa)continue;
            dfs1(so,no,de+1);

            if(son_num[so]>ma_num){
                ma_num=son_num[so];
                weight_son[no]=so;
            }
            son_num[no]+=son_num[so];
        }
    }
    void dfs2(int no,int fa,int to){
        new_idx[no]=++cnt;top[no]=to;idx[cnt]=no;
        if(weight_son[no])dfs2(weight_son[no],no,to);
        int so;
        for(int i=now[no];i;i=last[i]){
            so=go[i];
            if(so==fa||so==weight_son[no])continue;
            dfs2(so,no,so);
        }
    }
    void built(int id,int l,int r){
        if(l==r){
            tree[id]=w[idx[l]];
            return;
        }
        int mid=(l+r)>>1;
        built(id<<1,l,mid);
        built(id<<1|1,mid+1,r);
        tree[id]=(tree[id<<1]+tree[id<<1|1])%m;
    }

    void init(){
        deep[0]=0;
     dfs1(root,0,1);
     cnt=0;
     dfs2(root,0,root);
     built(1,1,len);
    }

    void moify(int id,T x,int l,int r,int ql,int qr){
        // 惰性更新当前节点
        tree[id]=(tree[id]+(T)(r-l+1)*lazy[id]%m)%m;
        // 如果不是叶子节点，则将lazy传播到子节点
        if(l!=r){
            lazy[id<<1]= (lazy[id<<1]+lazy[id])%m;
            lazy[id<<1|1]= (lazy[id<<1|1]+lazy[id])%m;
        }
        lazy[id]=0;
        // 如果当前节点完全在更新区间内
        if(ql<=l&&r<=qr){
            tree[id]=(tree[id]+(T)(r-l+1)*x%m)%m;
            // 如果不是叶子节点，则将diff传播到子节点
            if(l!=r){
                lazy[id<<1]= (lazy[id<<1]+x)%m;
                lazy[id<<1|1]= (lazy[id<<1|1]+x)%m;
            }
            return;
        }
        // 如果当前节点完全在更新区间外
        if (qr<l||r<ql)return;

        int mid=(l+r)>>1;
        moify(id<<1,x,l,mid,ql,qr);
        moify(id<<1|1,x,mid+1,r,ql,qr);
        tree[id]=(tree[id<<1]+tree[id<<1|1])%m;
    }


    T query(int id,int l,int r,int ql,int qr){
        // 惰性更新当前节点
        tree[id]=(tree[id]+(T)(r-l+1)*lazy[id]%m)%m;
        // 如果不是叶子节点，则将lazy传播到子节点
        if(l!=r){
            lazy[id<<1]= (lazy[id<<1]+lazy[id])%m;
            lazy[id<<1|1]= (lazy[id<<1|1]+lazy[id])%m;
        }
        lazy[id]=0;
        // 如果当前节点完全在更新区间内
        if(ql<=l&&r<=qr)return tree[id];

        // 如果当前节点完全在更新区间外
        if (qr<l||r<ql)return 0;

        int mid=(l+r)>>1;
        T res=(query(id<<1,l,mid,ql,qr)+query(id<<1|1,mid+1,r,ql,qr))%m;
        return res;
    }
    void op1(int x,int y,T z){
        while(top[x]!=top[y]){
            if(deep[top[x]]<deep[top[y]])swap(x,y);
            moify(1,z,1,len,new_idx[top[x]],new_idx[x]);
            x=f[top[x]];
        }
        if(deep[x]>deep[y])swap(x,y);
        moify(1,z,1,len,new_idx[x],new_idx[y]);
    }
    T op2(int x,int y){
        T res=0;
        while(top[x]!=top[y]){
            if(deep[top[x]]<deep[top[y]])swap(x,y);
            res+=query(1,1,len,new_idx[top[x]],new_idx[x]);
            res%=m;
            x=f[top[x]];
        }
        if(deep[x]>deep[y])swap(x,y);
        res+=query(1,1,len,new_idx[x],new_idx[y]);
        res%=m;
        return res;
    }
    void op3(int x,T z){
        moify(1,z,1,len,new_idx[x],new_idx[x]+son_num[x]-1);
    }
    T op4(int x){
        return  (query(1,1,len,new_idx[x],new_idx[x]+son_num[x]-1))%m;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m,rt,mm,u,v,op,x,y,z;
    cin>>n>>m>>rt>>mm;
    vector<ll>val(n+1,0);
    for(int i=1;i<=n;i++)cin>>val[i];
seg_tree<ll>pw(n,rt,mm,val);
for(int i=1;i<n;i++){
    cin>>u>>v;
    pw.add(u,v);pw.add(v,u);
}
pw.init();

while(m--){
    cin>>op;
    if(op==1){
        cin>>x>>y>>z;
        pw.op1(x,y,z);
    }
    else if(op==2){
        cin>>x>>y;
        cout<<pw.op2(x,y)<<endl;
    }
    else
        if(op==3){
        cin>>x>>z;
        pw.op3(x,z);
    }
    else {
        cin>>x;
        cout<<pw.op4(x)<<endl;
    }
}

    return 0;
}
