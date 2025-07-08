//题目链接：https://www.luogu.com.cn/problem/P10059
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
int  n, k, a[N], Max,sum=0;
deque<int>ma,mi;
void get_x(int m) {
    if(!ma.empty())ma.clear();
    if(!mi.empty())mi.clear();
    for(int i=1;i<m;i++){
        while(!ma.empty()&&a[ma.back()]<a[i])ma.pop_back();ma.push_back(i);
        while(!mi.empty()&&a[mi.back()]>a[i])mi.pop_back();mi.push_back(i);
    }
    for(int i=m;i<=n;i++){
        while(!ma.empty()&&a[ma.back()]<a[i])ma.pop_back();ma.push_back(i);
        while(!mi.empty()&&a[mi.back()]>a[i])mi.pop_back();mi.push_back(i);
        while (!ma.empty()&&ma.front()<=i-m)ma.pop_front();
        while (!mi.empty()&&mi.front()<=i-m)mi.pop_front();
        Max=min(Max,a[ma.front()]-a[mi.front()]);
    }
}
void ch(int m) {
    if(!ma.empty())ma.clear();
    if(!mi.empty())mi.clear();
    for(int i=1;i<m;i++){
        while(!ma.empty()&&a[ma.back()]<a[i])ma.pop_back();ma.push_back(i);
        while(!mi.empty()&&a[mi.back()]>a[i])mi.pop_back();mi.push_back(i);
    }
    for(int i=m;i<=n;i++){
        while(!ma.empty()&&a[ma.back()]<a[i])ma.pop_back();ma.push_back(i);
        while(!mi.empty()&&a[mi.back()]>a[i])mi.pop_back();mi.push_back(i);
        while (!ma.empty()&&ma.front()<=i-m)ma.pop_front();
        while (!mi.empty()&&mi.front()<=i-m)mi.pop_front();
        if(a[ma.front()]-a[mi.front()]>=Max)sum++;
        if(sum==k)return ;
    }
}
void solve(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++)cin >> a[i];
    int  l = 1, r = n - k + 1,mid;
    Max = INT_MAX;
    get_x(r);
    while (l <= r) {
        mid = (l + r) >> 1;
        sum=0;ch(mid);
        if (sum>=k)r = mid - 1;
        else l = mid + 1;
    }
    cout << Max << ' ' << l << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    cin>>T;
    while (T--)solve();
    return 0;
}
