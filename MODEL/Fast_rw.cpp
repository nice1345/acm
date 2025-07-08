
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
char buf[1<<20],*p1,*p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
template<typename T>inline void readT(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
template<typename T>
inline void writeT(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) writeT(x/10);
    putchar(x%10+'0');return;
}
inline void read128(__int128 &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}


void solve() {

}

int main() {
    freopen("in.in","r",stdin); //输入重定向，输入数据将从in.in文件中读取
    freopen("out.out","w",stdout); //输出重定向，输出数据将保存out.out文件中


    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    //cin>>T;
    while (T--) {
        solve();
    }

    return 0;
}
