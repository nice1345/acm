#include<bits/stdc++.h>
using namespace std;
//题目链接：https://codeforces.com/gym/104252/my
//题解：https://blog.csdn.net/kai_wei_/article/details/129979280#:~:text=2021-2022
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string s;int d;cin>>s>>d;
    int ans=0;
    while (!s.empty()){
        ans++;
        vector<int> p={0};
        int i=1,j=0;
        for(;i<s.size();i++){
            while(j>0&&s[i]!=s[j])j=p[j-1];
            if(s[i]==s[j])j++;
            p.emplace_back(j);
            if(i-p[i]>=d)break;
            /**
             喵的，写成下面这一行只能说对kmp理解不太深，不如看看上面链接人家咋写的
             * */
            //if(p.size()>d&&p[(int)p.size()-1]!=p[(int)p.size()-2]+1)break;
        }
        if(i==s.size())break;
        s.erase(s.begin(),s.begin()+i);
    }
    cout<<ans<<"\n";
    return 0;
}