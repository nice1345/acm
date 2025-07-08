
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
int la=(int)a.length();
vector<vector<int>>dfa(26,vector<int>(la));
vector<int>p(la);
dfa[(int)(a[0]-'a')][0]=1;
for(int i=1,j=0;i<la;i++){
for(int c=0;i<26;i++){
    dfa[c][i]= dfa[c][j];
}
//dfa[pat[j]-'tree'][j]记录字符串路径
dfa[(int)(a[i]-'a')][i]=i+1;
/**记录往前匹配的字符串路径
* dfa[tree[j]-'tree'][j]
* 由于前面已经保存过状态
* 只需将当前的状态赋给j(一步到位)
* */
j=dfa[(int)(a[i]-'a')][j];
p[i]=j;
}


string b;
cin>>b;
int lb=(int)b.length();
for(int i=0,j=0;i<lb;i++){
    j=dfa[(int)(b[i]-'a')][j];
    if(j==la){
        // 找位置就break;
        // 找个数就j=p[j-1];
        break;
    }
}
    return 0;
}