#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    cin>>_;
    for(int i=1;i<=_;i++){
        cout<<"Case #"<<i<<":\n";
        int n;cin>>n;
        vector<int>d(63,0);
        bool flag=0;
        for(int i=0;i<n;i++){
            int ne;cin>>ne;
            while(ne){
                int w=__lg(ne);
                if(!d[w]){
                    d[w]=ne;
                    break;
                }
                ne^=d[w];
            }
            if(!ne)flag=1;
        }
        vector<int>h;
        for(int i=0;i<=62;i++)
            if(d[i]){
                for(int w=i-1;w>=0;w--)
                    if((d[i]>>w)&1)
                        d[i]^=d[w];
                h.emplace_back(d[i]);
            }
        int q;cin>>q;
        while(q--){
            int k;cin>>k;
            if(flag)k--;
            int res=0;
            int w=0;
            while(k){
                if(w>=h.size()) {
                    res=-1;
                    break;
                }
                if(k&1)res^=h[w];
                w++;
                k>>=1;
            }
            cout<<res<<"\n";
        }
    }
    return 0;
}