#include<bits/stdc++.h>
using namespace std;
/**
 任意两个相邻的小矩形相邻的边会抵消成0形成一个更大的矩形
 任意一个矩形的修改，都可以下放到最小的2x2的小矩形，因此，我们只需在要修改的地方用2x2的小矩形修改即可。
 * */
int n,m,d;
char ne;
int a[505][505],ans[505][505];
void solve() {
cin>>n>>m;
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        cin>>ne;
        a[i][j]=ne-'0';
    }
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        cin>>ne;
        ans[i][j]= ne - '0';
    }
    function<void(int&, int)> add = [&](int &x, int c) {
        x = (x + c) % 3;
    };
for(int i=1;i<n;i++)
    for(int j=1;j<m;j++){
        if (a[i][j] == ans[i][j]) continue;
        d = (ans[i][j] - a[i][j] + 3) % 3;
        add(a[i][j], d), add(a[i + 1][j + 1], d);
        add(a[i + 1][j], 3 - d), add(a[i][j + 1], 3 - d);
    }
//
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++)
//            cout<<a[i][j];
//        cout<<"\n";
//    }
//    for(int i=1;i<=n;i++) {
//        for (int j = 1; j <= m; j++)
//            cout << sum[i][j];
//        cout << "\n";
//    }
for(int i=1;i<=n;i++)
    if(a[i][m] != ans[i][m]){
        cout<<"NO\n";
        return;
    }
for(int i=1;i<=m;i++)
    if(a[n][i] != ans[n][i]){
        cout<<"NO\n";
        return;
    }
cout<<"YES\n";



}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin>>_;
    for (int i = 1; i <= _; i++) {
        solve();
    }
    return 0;
}
