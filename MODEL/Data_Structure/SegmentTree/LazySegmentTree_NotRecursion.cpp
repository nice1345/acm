//题目链接:https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pil pair<int,long long>
#define pli pair<long long,int>
#define vec vector
#define vii vector<int>
#define vll vector<long long>
using namespace std;
typedef long long ll;
//#define int long long
const int mod=10007;
const int N=2e5+5;
template <typename T>
T read() {
    T sum = 0, fl = 1;  // 将 sum,fl 和 ch 以输入的类型定义
    int ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') fl = -1;
    for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
    return sum * fl;
}
template <typename T>
void read(T &sum) {
    sum=0;
    bool fl=1;  // 将 sum,fl 和 ch 以输入的类型定义
    int ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') fl = 0;
    if(fl){
        for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
    }
    else{
        for (; isdigit(ch); ch = getchar()) sum = sum * -10 - (ch - '0');
    }
    //  return sum * fl;
}
template <typename T>
void write(T x) {
    static int sta[35];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}

template<class T>
struct SegmentTree{
    struct node{
        int l=0,r=0,ls=0,rs=0,fa=-1;
        T lazy=0,val=0;
    };
    vector<node> tree;
    vector<int>idx;
    //初始化一个[0,a.size()-1]的线段树
    SegmentTree(vector<T> &a){
        //使用前缀和优化,省去回溯操作
        for(auto j=a.begin(),i=a.begin()+1;i!=a.end();i++,j++)*i+=*j;
        int bound=(int)a.size()-1;
        int len=bound*2+1;
        tree.resize(len);idx.resize(bound + 1);
        tree[0].l=0;tree[0].r=bound;
        int cnt=1;
        for(int i=0;i<len;i++){
            if(tree[i].l==tree[i].r){
                if(tree[i].l==0)
                    tree[i].val=a[0];
                else
                    tree[i].val=a[tree[i].r]-a[tree[i].l-1];
                idx[tree[i].l]=i;
            }
            else{
                if(tree[i].l==0)
                    tree[i].val=a[tree[i].r];
                else
                    tree[i].val=a[tree[i].r]-a[tree[i].l-1];
                int mid=(tree[i].l+tree[i].r)>>1;
                tree[cnt].l=tree[i].l;tree[cnt].r=mid;
                tree[cnt].fa=i;tree[i].ls=cnt;cnt++;
                tree[cnt].l=mid+1;tree[cnt].r=tree[i].r;
                tree[cnt].fa=i;tree[i].rs=cnt;cnt++;
            }
        }
    }
    //初始化一个[0,x]的全0的线段树
    SegmentTree(int x){
        int bound=x,len=bound*2+1;
        tree.resize(len);idx.resize(bound + 1);
        tree[0].l=0;tree[0].r=bound;
        int cnt=1;
        for(int i=0;i<len;i++){
            if(tree[i].l!=tree[i].r){
                int mid=(tree[i].l+tree[i].r)>>1;
                tree[cnt].l=tree[i].l;tree[cnt].r=mid;
                tree[cnt].fa=i;tree[i].ls=cnt;cnt++;
                tree[cnt].l=mid+1;tree[cnt].r=tree[i].r;
                tree[cnt].fa=i;tree[i].rs=cnt;cnt++;
            }
            else idx[tree[i].l]=i;
        }
    }
    //单修把a[l]变成v
    void update1(int l,T v){
        //此类操作无发和有懒标记的操作(区加单加)一起使用
        //从底层根节点往上修改即可
        tree[idx[l]].val=v;
        int id=tree[idx[l]].fa;
        while(id!=-1){
            tree[id].val=tree[tree[id].ls].val+tree[tree[id].rs].val;
            id=tree[id].fa;
        }
    };
    //单加把a[idx]加上v
    void update(int l,T v){
        //从底层根节点往上加即可
        int id=idx[l];
        while(id!=-1){
            tree[id].val+=v;
            id=tree[id].fa;
        }

    };
    //区加把a[ql,qr]都加上v
    void moify(int ql,int qr,T v){
        //判断单加还是区加
        if(ql==qr){
            update(ql,v);
            return;
        }
        //找到一个左右儿子都与修改区间有交且区间长度最大的节点编号(要修改的所有区间节点的最近公共祖先),因为筛去了单加,此节点一定不是叶子节点也就有左右儿子
        int id=0;
        while(true){
            //当前节点区间肯定有交集(包含修改节点区间),直接更新值
            tree[id].val+=v*(T)(qr-ql+1);
            //左儿子与修改区间没有交集,节点向右儿子传递
            if(tree[tree[id].ls].r<ql){
                id=tree[id].rs;continue;
            }
            else if(qr<tree[tree[id].rs].l){
                id=tree[id].ls;continue;
            }
            break;
        }
        //如果刚好相等,那么需要修改的区间节点就这一个
        if(tree[id].l==ql&&tree[id].r==qr){
            tree[tree[id].ls].lazy+=v;
            tree[tree[id].rs].lazy+=v;
            return;
        }
        /**向左下修改
        节点区间与修改区间一定有交
        节点区间与修改区间的交集形式一定是节点区间在左边,修改区间在右边
        交集长度:tree[id].r-ql+1
        左右儿子与修改区间的交集情况一定是
        左儿子有交,右儿子一定全包含
        左儿子没交,右儿子一定有交
        */
        int cnt=id;
        id=tree[cnt].ls;
        while(true){
            //修改区间包含当前节点区间,惰性更新
            if(ql==tree[id].l){
                tree[id].lazy+=v;
                break;
            }
            else{
                //当前节点区间与修改区间有交集,查出交集大小实时更新
                tree[id].val+=v*(T)(tree[id].r-ql+1);
                //左儿子没交,右儿子一定有交
                if(tree[tree[id].ls].r<ql)
                    id=tree[id].rs;

                    //左儿子有交,右儿子一定全包含
                else{
                    //右儿子被包含,惰性更新
                    tree[tree[id].rs].lazy+=v;
                    id=tree[id].ls;
                }
            }
        }
        //同理向右下修改
        id=tree[cnt].rs;
        while(true){
            //修改区间包含当前节点区间,惰性更新
            if(tree[id].r==qr){
                tree[id].lazy+=v;
                break;
            }
            else{
                //当前节点区间与修改区间有交集,查出交集大小实时更新
                tree[id].val+=v*(T)(qr-tree[id].l+1);
                //右儿子没交,左儿子一定有交
                if(qr<tree[tree[id].rs].l)
                    id=tree[id].ls;

                    //右儿子有交,左儿子一定全包含
                else{
                    //左儿子被包含,惰性更新
                    tree[tree[id].ls].lazy+=v;
                    id=tree[id].rs;
                }
            }
        }
    }
    //不带懒标记的单查
    T quire1(int l){return tree[idx[l]].val;}
    //带懒标记的单查
    T quire(int l){
        int id=0;
        while(true){
            tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
            if(tree[id].l==tree[id].r){
                tree[id].lazy=0;
                break;
            }
            else{
                tree[tree[id].ls].lazy+=tree[id].lazy;
                tree[tree[id].rs].lazy+=tree[id].lazy;
                tree[id].lazy=0;
                if(l<=tree[tree[id].ls].r)id=tree[id].ls;
                else id=tree[id].rs;
            }
        }
        return tree[id].val;
    }
    //查询a[ql,qr]区间之和
    T query(int ql,int qr){
        //看看是单查还是区查
        if(ql==qr)return quire(ql);
        //找到一个左右儿子都与查询区间有交且区间长度最大的节点编号(要查询的所有区间节点的最近公共祖先),因为筛去了单查,此节点一定不是叶子节点也就有左右儿子
        int id=0;
        while(true){
            //当前节点区间肯定有交集(包含查询节点区间),直接更新值
            tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
            //一定有左右儿子,不用特判,直接向下惰性更新
            tree[tree[id].ls].lazy+=tree[id].lazy;
            tree[tree[id].rs].lazy+=tree[id].lazy;
            tree[id].lazy=0;
            //左儿子与查询区间没有交集,节点向右儿子传递
            if(tree[tree[id].ls].r<ql){
                id=tree[id].rs;continue;
            }
            else if(qr<tree[tree[id].rs].l){
                id=tree[id].ls;continue;
            }
            break;
        }
        //如果刚好相等,那么需要查询的区间节点就这一个
        if(tree[id].l==ql&&tree[id].r==qr)return tree[id].val;
        T res=0;
        int cnt=id;
        //向左下更新
        id=tree[cnt].ls;
        while(true){
            //查询区间包含当前节点区间
            if(ql==tree[id].l){
                tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
                res+=tree[id].val;
                //特判叶子节点
                if(tree[id].l!=tree[id].r){
                    tree[tree[id].ls].lazy+=tree[id].lazy;
                    tree[tree[id].rs].lazy+=tree[id].lazy;
                }
                tree[id].lazy=0;
                break;
            }
            else{
                tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
                //当前节点区间与查询区间有交集且非包含,那就一定不是叶子节点
                tree[tree[id].ls].lazy+=tree[id].lazy;
                tree[tree[id].rs].lazy+=tree[id].lazy;
                tree[id].lazy=0;
                //左儿子没交,右儿子一定有交
                if(tree[tree[id].ls].r<ql)
                    id=tree[id].rs;

                    //左儿子有交,右儿子一定全包含
                else{
                    //右儿子被包含,惰性更新
                    tree[tree[id].rs].val+= tree[tree[id].rs].lazy*(T)(tree[tree[id].rs].r-tree[tree[id].rs].l+1);
                    res+=tree[tree[id].rs].val;
                    //特判叶子节点
                    if(tree[tree[id].rs].l!=tree[tree[id].rs].r){
                        tree[tree[tree[id].rs].ls].lazy+=tree[tree[id].rs].lazy;
                        tree[tree[tree[id].rs].rs].lazy+=tree[tree[id].rs].lazy;
                    }
                    tree[tree[id].rs].lazy=0;
                    id=tree[id].ls;
                }
            }
        }
        //向右下更新
        id=tree[cnt].rs;
        while(true){
            //查询区间包含当前节点区间
            if(qr==tree[id].r){
                tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
                res+=tree[id].val;
                //特判叶子节点
                if(tree[id].l!=tree[id].r){
                    tree[tree[id].ls].lazy+=tree[id].lazy;
                    tree[tree[id].rs].lazy+=tree[id].lazy;
                }
                tree[id].lazy=0;
                break;
            }
            else{
                tree[id].val+= tree[id].lazy*(T)(tree[id].r-tree[id].l+1);
                //当前节点区间与查询区间有交集且非包含,那就一定不是叶子节点
                tree[tree[id].ls].lazy+=tree[id].lazy;
                tree[tree[id].rs].lazy+=tree[id].lazy;
                tree[id].lazy=0;
                //右儿子没交,左儿子一定有交
                if(qr<tree[tree[id].rs].l)
                    id=tree[id].ls;

                    //右儿子有交,左儿子一定全包含
                else{
                    //左儿子被包含,惰性更新
                    tree[tree[id].ls].val+= tree[tree[id].ls].lazy*(T)(tree[tree[id].ls].r-tree[tree[id].ls].l+1);
                    res+=tree[tree[id].ls].val;
                    //特判叶子节点
                    if(tree[tree[id].ls].l!=tree[tree[id].ls].r){
                        tree[tree[tree[id].ls].ls].lazy+=tree[tree[id].ls].lazy;
                        tree[tree[tree[id].ls].rs].lazy+=tree[tree[id].ls].lazy;
                    }
                    tree[tree[id].ls].lazy=0;
                    id=tree[id].rs;
                }
            }
        }
        return res;
    }
    //打印树结构
    void print(){
        vector<vector<node>>q(30);
        q[0].push_back(tree[0]);
        for(int i=0;i<30;i++){
            if(q[i].empty())break;
            for(node j:q[i]){
                cout<<"[ ";
                cout<<j.l<<" "<<j.r<<" "<<j.val<<" "<<j.lazy;
                cout<<" ]";
                if(j.l!=j.r){
                    q[i+1].push_back(tree[j.ls]);
                    q[i+1].push_back(tree[j.rs]);
                }
            }
            cout<<"\n";
        }
    }
};
void solve(){

}

int main(){
//    cin.tie(0)->sync_with_stdio(0);
//    int T=1;
//    //cin>>T;
//    for(int T=1;T<=T;T++){
//        solve();
//    }


//    int len,m;
//    cin>>len>>m;
//    vector<ll>a(len+1,0);
//    for(int i=1;i<=len;i++)cin>>a[i];
//    SegmentTree<ll>tr(a);
//    while(m--){
//        int op,x,y;ll z;
//        cin>>op;
//        if(op==1){
//            cin>>x>>y>>z;
//            tr.moify(x,y,z);
//        }
//        else{
//            cin>>x>>y;
//            cout<<tr.query(x,y)<<"\len";
//        }
//    }


//cout<<pw;

    int n,m;
    read<int>(n);read<int>(m);
    vector<ll>a(n);
    for(ll &i:a)read<ll>(i);
    SegmentTree<ll>tr(a);
    int op,x,y;ll z;
    while(m--){
        read<int>(op);read<int>(x);read<int>(y);
        x--;y--;
        if(op==1){
            read<ll>(z);
            tr.moify(x,y,z);
        }
        else{
            write(tr.query(x,y));
            putchar('\n');
        }
    }
    return 0;
}