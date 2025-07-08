#include<bits/stdc++.h>
using namespace std;
/**
 离谱，能折就折
 * */
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int _;cin>>_;
    while (_--){

        /**
              now
         l    r i  j
         012345 5432
         101010|0101
         折过去的新端点为now-(j-i)=new
         dir为方向
         l=min(l,r,new)
         r=max(l,r,new)
         * */
        int n; cin >> n;
        string s; cin >> s;
        int now = 0, l = 0, r = 0;
        int dir = 1;
        for (int i = 0, j; i < n; i = j) {
            for (j = i + 1; j < n && s[j] != s[j - 1]; j++);
            now += (j - i) * dir;
            l = min(l, now), r = max(r, now);
            dir *= -1;
        }
        cout << r - l << '\n';


//        int n; cin >> n;
//        string s; cin >> s;
//        int now = 0, l = 0, r = 0;
//        for (int i = 0; i < n; i++) {
//            now += (i & 1) ^ (s[i] - '0') ? 1 : -1;
//            l = min(l, now), r = max(r, now);
//        }
//        cout << r - l << '\n';
    }
    return 0;
}