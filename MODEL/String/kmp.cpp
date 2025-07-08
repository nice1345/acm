
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string a;
    cin>>a;
    int n=(int)a.length();
    vector<int>p(n);
    for(int i=1,j=0;i<n;i++){
        /**
       下标从0开始,tree[j]没匹配上
        就找a[j-1]的真前缀,即下一个匹配点
       */
        while(j>0&&a[j]!=a[i])j=p[j-1];
        if(a[i]==a[j])j++;
        p[i]=j;
    }
   string s;
    cin>>s;
    int ls=(int)s.length();
    for(int i=0,j=0;i<ls;i++){
        while(j>0&&s[i]!=a[j])j=p[j-1];
        if(s[i]==a[j])j++;
        if(j==n){
            // 找位置就break;
            // 找个数就j=p[j-1];
            break;
        }
    }



    return 0;
}