//题解:https://blog.csdn.net/qq_45809243/article/details/138582718
#include <iostream>
using namespace std;
typedef long long ll;

int T,n,m;

int gcd(int a,int b){
    while(b)b^=a^=b^=a%=b;
    return a;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        ll ans=0;
        for(int x=1;x*x<=n;x++)
            for(int y=1;y*y<=m;y++)
                if(gcd(x,y)==1)
                    ans+=min(n/(x*(x+y)),m/(y*(x+y)));
        cout<<ans<<endl;
    }
    return 0;
}
