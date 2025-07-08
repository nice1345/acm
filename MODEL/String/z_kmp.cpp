
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r)z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])z[i]++;
        if(i + z[i] > r) {l = i;r = i + z[i];}
    }
    return z;
}
/**
 [l,r-1]是已知r最大的与s匹配的前缀 s[l,r-1]==s[0,r-l-1]
 i<r
 i  在 [l,r-1]的位置相当于i-l在[0,r-l-1]的位置
 那么z[i] = min(r - i, z[i - l]);
 r后面的长度暴力计算
 复杂度就是r向右跑了几步
 oi-wiki上面的代码写的简单明了
 * */
signed main() {


    return 0;
}