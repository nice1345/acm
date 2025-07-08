#include<bits/stdc++.h>
using namespace std;
//https://blog.csdn.net/m0_49041421/article/details/107664675
//https://zhuanlan.zhihu.com/p/569087153
int sg[101];
bool vis[111];
int main(){
    sg[0]=0;vis[0]=1;
    for(int i=1;i<=100;i++){
        for(int j=1;j<=110;j++)vis[j]=0;
        for(int j=1;j<i;j++){
            vis[sg[j]]=1;
            for(int k=1;j+k<i;k++)
                vis[sg[j]^sg[k]]=1;
        }
        int ne=0;
        while(vis[ne])ne++;
        sg[i]=ne;
    }
    int n,x;
    while(~scanf("%d",&n)){
        int f=0,s=0;
        while(n--){
            scanf("%d",&x);
            s^=sg[x];
            if(x>1) f=1;
        }
        if(s&&f||!s&&!f) printf("Yes\n");
        else printf("No\n");
    }

//    int N;
//    while(cin >> N) {
//        int ans = 0, maxx = 0;
//        for(int i=1;i<=N;++i) {
//            int x; cin >> x; ans ^= sg[x]; maxx = max(maxx,sg[x]);
//        }
//        if( (maxx==1&&ans==0) || (maxx>1&&ans>0) ) cout << "Yes\n";
//        else cout << "No\n";
//    }



//反nim
//    int n,x;
//    while(~scanf("%d",&n)){
//        int f=0,s=0;
//        while(n--){
//            scanf("%d",&x);
//            s^=x;
//            if(x>1) f=1;
//        }
//        if(s&&f||!s&&!f) printf("Yes\n");
//        else printf("No\n");
//    }
    return 0;
}
