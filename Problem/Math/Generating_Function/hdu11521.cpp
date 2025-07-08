#include <bits/stdc++.h>
using namespace std;
const int maxm=11;
double tree[maxm],open[maxm];
int num[maxm];
double nn[maxm];//存阶乘的值
int n,m;
void init(){//预处理阶乘的值
    nn[0]=1;
    for(int i=1;i<maxm;i++){
        nn[i]=nn[i-1]*i;
    }
}
signed main(){
    init();
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            cin>>num[i];
        }
        for(int i=1;i<=m;i++){
            tree[i]=0;
        }
        tree[0]=1;
        for(int k=1;k<=n;k++){
            for(int i=0;i<=num[k]&&i<=m;i++){//i属于第k个数
                for(int j=0;i+j<=m;j++){//tree[j]为前面k-1个数的排列j的系数
                    open[i + j]+= tree[j] / nn[i];
                }
            }
            for(int i=0;i<=m;i++){
                tree[i]=open[i];
                open[i]=0;
            }
        }
        //输出要用0.f或者0.lf不能强制类型转化成int，会wa
        printf("%.0f\n", tree[m] * nn[m]);//乘上阶乘消去分母才是答案a[m]
    }
    return 0;
}
