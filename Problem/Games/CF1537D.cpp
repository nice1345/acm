#include<bits/stdc++.h>
using namespace std;
//https://www.cnblogs.com/hznumqf/p/15189749.html
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    set<int>h;
    int ne=2;
    while(ne<=1e9){
        h.insert(ne);
        ne*=4ll;
    }
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        int n;cin>>n;
        if(n&1||h.contains(n))cout<<"Bob\n";
        else cout<<"Alice\n";
    }
    return 0;
}
