#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int long long;
ll mod=(ll)998244353;
//const int N=13000005;

ll n,m;
ll q,w;

void solve(){
    cin>>n>>m;
    vector<vector<ll>>pw(n+1,vector<ll>(m+1,0));
    q=n*(n+1)/2;w=m*(m+1)/2;
    vector<ll>h;
    ll fl=0;
    if(q%2==0){
        q/=2;
        ll no=n;
        ll id=n;
        while (no<q&&id){
            ll l;
            for( l=2;l<=id;l++){
                ll add=l*(l-1)/2,add1=l*(l+1)/2;
                if(((add+no)<=q)&&((add1+no)>q))break;
                if(l==id)break;
            }
            id-=l;
            no+=(l*(l-(ll)1)/(ll)2);
            h.push_back(l);
        }
        //  cout<<no<<endl;
//  for(int i:h)cout<<i<<" ";
        cout<<"\n";
        if(no==q){
            while (id){
                h.push_back(1);id--;
            }
            ll st=0,nn=0;
            fl=1;
            cout<<"Yes"<<endl;
            for(ll e:h){
                for(ll i=st;i<st+e;i++){
                    for(ll j=0;j<m;j++)
                        cout<<nn<<" ";
                    cout<<"\n";
                }
                st+=e;
                nn=1-nn;
            }
        }
    }
    h.clear();
    if(!fl){
        if(w%2==0){
            w/=2;
            ll no=m;
            ll id=m;
            while (no<w&&id){
                ll l;
                for( l=2;l<=id;l++){
                    ll add=l*(l-1)/2,add1=l*(l+1)/2;
                    if(((add+no)<=w)&&((add1+no)>w))break;
                    if(l==id)break;
                }
                id-=l;
                no+=(l*(l-(ll)1)/(ll)2);
                h.push_back(l);
            }
            if(no==w){
                while (id){
                    h.push_back(1);id--;
                }
                ll st=0,nn=0;
                fl=1;
                cout<<"Yes"<<endl;
                for(ll e:h){
                    for(ll i=st;i<st+e;i++){
                        for(ll j=0;j<n;j++)
                            pw[j][i]=nn;
                    }
                    st+=e;
                    nn=1-nn;
                }
                for(ll i=0;i<n;i++){
                    for(ll j=0;j<m;j++)cout<<pw[i][j]<<" ";
                    cout<<"\n";
                }
            }
            else
                cout<<"No"<<endl;
        }
        else cout<<"No"<<endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}
