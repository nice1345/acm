//题解:https://www.cnblogs.com/cpchenpi/p/-/CF1965-solutions
/**
 先手一步后，如果后手一步的状态可以被先手走到(后手全部的状态被先手包含)，那么先手一定必胜
 如果有一次选择的k>1&&k<=a;
 假设k选a为必胜，那肯定选k=a;
 否则选k=a-1,那下一个人必选k=1;
 所以先手必胜
 * */
#include<bits/stdc++.h>
using namespace std;
int main( )
{
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while (_--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        n = a.size();
        int round = 0;
        for (int i = n - 1; i > 0; i--) a[i] -= a[i - 1];
        reverse(a.begin(), a.end());
        while (a.size() && a.back() == 1) {
            a.pop_back(), round ^= 1;
        }
        if (a.size() == 0) round ^= 1;
        cout << (round ? "Bob" : "Alice") << '\n';
    }
    return 0;
}