#include <bits/stdc++.h>
using namespace std;
int t,n,c,d;
string s = "qkj";
int a[3][200003];
int b[3];
pair<char,int>suf[200003];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin>>n;
        b[0]=b[1]=b[2]=n;
        suf[1]={'-',0};
        for(int i=0;i<3;++i)
            for(int j=1;j<=n;++j)
                cin>>a[i][j];
        for(int i=n-1;i>0;--i){
            c=-1;
            for(int j=0;j<3;++j)
                if(a[j][i]>a[j][b[j]])
                    c=j;
            if(c==-1)continue;
            //记录路径
            suf[i]={s[c],b[c]};
            //让到达i=1时，交换的物品更小
            for(int j=0;j<3;++j)
                if(a[j][i]<a[j][b[j]])
                    b[j]=i;
        }
        if(!suf[1].second){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        c=0;d=1;
        while(d!=n){++c;d=suf[d].second;}
        cout<<c<<"\n";
        d=1;
        while(d!=n){cout<<suf[d].first<<" "<<suf[d].second<<"\n";d=suf[d].second;}
    }
}