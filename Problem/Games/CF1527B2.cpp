#include<bits/stdc++.h>
using namespace std;
//题解链接：https://www.luogu.com.cn/article/67pzyy9l
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int _,n;
    string s;
    cin>>_;
    for(int i=1;i<=_;i++){
        cin>>n>>s;
        int l=0,r=n-1,o=0,a=0,b=0,d=0;
        bool h=0;
        while(l<r){
            if(s[l]==s[r]&&s[l]=='0')o++;
            else if(s[l]=='0'||s[r]=='0')b++;
            l++;r--;
        }
        if(l==r&&s[l]=='0')h=1;
        int q=0,w=0;
        if(h){
            if(o)w=1;
            else q=1;
        }
        else {
            if(o)q=2;
        }
        if(b&&q>w){
            a+=w;b+=q;
            b--;a++;
        }
        else{
            a+=q;b+=w;
        }
        if(a<b)cout<<"ALICE\n";
        else if(a>b)cout<<"BOB\n";
        else cout<<"DRAW\n";
    }
    return 0;
}
