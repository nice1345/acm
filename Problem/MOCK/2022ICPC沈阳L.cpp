#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int long long;
ll mod=(ll)998244353;
//const int N=13000005;
int n[2];
double ans[3];
int aa[7][2];//存攻击力
int a[7][2];//存血量
int k[7][2];//存攻击次数
// st攻击方，1-st被攻击方
void mm(int st,double d){
    //先判断回合是否结束
    bool q1=true,q2=true,q3=true;
    for(int i=0;i<n[0];i++)if(a[i][0]>0)q1=false;
    for(int i=0;i<n[1];i++)if(a[i][1]>0)q2=false;
    q3=q1&&q2;
    if(q3){
        ans[2]+=d;
        return;
    }
    if(q1){
        ans[1]+=d;
        return;
    }
    if(q2){
        ans[0]+=d;
        return;
    }
    //在判断该谁攻击，存在id里
    int id=0,ma=INT_MAX;
    for(int i=0;i<n[st];i++)
        if(a[i][st]>0)
            if(ma>k[i][st])
                ma=k[i][st];

    for(int i=0;i<n[st];i++)
        if(a[i][st]>0)
            if(ma==k[i][st]){
                id=i;break;
            }

    double sum=0;
    int y,yy;
    //看看被攻击方有几人还活着,也就是还有几个人可以编号id可以攻击
    for(int i=0;i<n[1-st];i++)if(a[i][1-st]>0)sum++;
    for(int i=0;i<n[1-st];i++){

        if(a[i][1-st]>0){
            y=a[i][1-st];yy=a[id][st];
            a[i][1-st]-=aa[id][st];
            a[id][st]-=aa[i][1-st];
            k[id][st]++;
            //对于每个可以攻击的人，id随机攻击到它的概率为1/sum,在乘上走到当前的概率
            //该到对面攻击了
            mm(1-st,d/sum);
            //回溯
            a[i][1-st]=y;a[id][st]=yy;
            k[id][st]--;
        }
    }
}

void solve(){
    cout<<setiosflags(ios::fixed)<<setprecision(10);
    cin>>n[0]>>n[1];
    ans[0]=0;ans[1]=0;ans[2]=0;
    for(int i=0;i<n[0];i++){
        cin>>aa[i][0];
        a[i][0]=aa[i][0];
    }
    for(int i=0;i<n[1];i++){
        cin>>aa[i][1];
        a[i][1]=aa[i][1];
    }
    if(n[0]>n[1]){
        mm(0,(double)1);
    }
    else if(n[0]<n[1]){
        mm(1,(double)1);
    }
    else {
        mm(0,(double)0.5);
        mm(1,(double)0.5);
    }
    //cout<<fixed<<setprecision(13)<<ans[0]<<endl;//保留13位小数
          cout<<ans[0]<<endl;
    cout<<ans[1]<<endl;
    cout<<ans[2]<<endl;

}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    //cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}