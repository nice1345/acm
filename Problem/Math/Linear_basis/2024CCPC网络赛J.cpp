#include<bits/stdc++.h>
using namespace std;
//题目链接：https://codeforces.com/gym/105336
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int __=1;
    cin>>__;
    for(int _=1;_<=__;_++){
        int n;cin>>n;
        vector<int>a(n),b(n),d(31,0);
        int a1=0,b1=0;
        for(int &i:a)cin>>i, a1^=i;
        for(int &i:b)cin>>i, b1^=i;
        for(int i=0;i<n;i++){
            int cur=a[i]^b[i];
            while(cur){
                int w=__lg(cur);
                if(d[w])cur^=d[w];
                else{
                    d[w]=cur;
                    break;
                }
            }
        }
        bool flag=0;
        for(int i=30;i>=0;i--){
            int a2= (a1 >> i) & 1,b2= (b1 >> i) & 1;
            if(a2 == 1 && b2 == 1){ a1^=d[i];b1^=d[i];}
            else if(a2 == 0 && b2 == 1){
                if(!flag){
                    flag=1;
                    a1^=d[i];b1^=d[i];
                }
            }
            else if(a2 == 1 && b2 == 0){
                if(!flag)flag=1;
                else {a1^=d[i];b1^=d[i];}
            }
        }
        cout << a1 << "\n";
    }
    return 0;
}