#include<bits/stdc++.h>
using namespace std;
template <class S, bool (*op)(S, S)>
struct cartesian_tree{
    vector<int>ls,rs;
    vector<S>tree;
    int root;
    //建树
    cartesian_tree(vector<S> &a,bool i1){
        int n=a.size();
        tree.resize(n);ls.resize(n);rs.resize(n);
        vector<S>st(n);
        int cnt=-1;
        for(int i=i1?1:0;i<n;i++){
            ls[i]= rs[i]=-1;tree[i]=a[i];
            bool flag=0;//i节点是否有左儿子
            while(cnt!=-1&&op(tree[i],tree[st[cnt]]))cnt--,flag=1;
            //如果找到i的左边比他优先级大的第一个节点，将那个节点的右儿子更新为i
            if(cnt!=-1)rs[st[cnt]]=i;
            if(flag)ls[i]=st[cnt+1];
            st[++cnt]=i;
        }
        root=st[0];
    }
    //测试
    void test(int cur){
        if(ls[cur]!=-1)test(ls[cur]);
        cout<<tree[cur]<<" ";
        if(rs[cur] != -1)test(rs[cur]);
    }
    void printf_tree(){
        test(root);
    }
    //写自己做题的逻辑
    int res=0;
    int dfs(int cur){
        int sum=1;
        if(ls[cur]!=-1)sum+=dfs(ls[cur]);
        if(rs[cur] != -1)sum+=dfs(rs[cur]);
        res=max(res,sum*tree[cur]);
        return sum;
    }
};
//小根堆
bool mir(int a,int b){return a<b;}
//大根堆
bool mar(int a,int b){return a>b;}
//hdu1560:https://acm.hdu.edu.cn/showproblem.php?pid=1506
int main(){
    cin.tie(0)->sync_with_stdio(0);
    while(true){
        int n;cin>>n;
        if(n==0)break;
        vector<int>a(n);for(int &i:a)cin>>i;
        cartesian_tree<int,mir>tr(a,0);
        tr.dfs(tr.root);
        cout<<tr.res<<"\n";
    }
    return 0;
}
