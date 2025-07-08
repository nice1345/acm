#include <bits/stdc++.h>
#define pii pair<int,int>
#define pil pair<int,long long>
#define pli pair<long long,int>
#define vec vector
#define vii vector<int>
#define vll vector<long long>
using namespace std;
typedef long long ll;
char buf[1<<20],*p1,*p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
inline void readT(int &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
inline void writeT(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) writeT(x/10);
    putchar(x%10+'0');return;
}
//#define int long long
ll mod=(ll)998244353;
const int N = 5e5 + 5;
/**加强版*/
int main(){
    static const int maxn = 500010;
    int t;
    readT(t);
    while (t--) {
        int n, k;
        static int a[maxn];
        readT(n);readT(k);
        for (int i = 1; i <= n; i++)
            readT(a[i]);
        int X = INT_MAX, L = n + 1 - k;
        static int sMi[maxn], fMi, eMi;
        static int sMx[maxn], fMx, eMx;
        fMi = fMx = 1, eMi = eMx = 0;
        for (int i = 1; i <= n; i++) {
            while (fMi <= eMi && a[sMi[eMi]] >= a[i]) eMi--;
            while (fMx <= eMx && a[sMx[eMx]] <= a[i]) eMx--;
            sMi[++eMi] = sMx[++eMx] = i;
            //大神写法
            fMi += sMi[fMi] == i - L;
            fMx += sMx[fMx] == i - L;
            if (i >= L)
                X = min(X, a[sMx[fMx]] - a[sMi[fMi]]);
        }
        static int cnt[maxn];
        memset(cnt, 0, sizeof(cnt));
        fMi = fMx = 1, eMi = eMx = 0;
        for (int i = 1, l = 1; i <= n; i++) {
            while (fMi <= eMi && a[sMi[eMi]] >= a[i]) eMi--;
            while (fMx <= eMx && a[sMx[eMx]] <= a[i]) eMx--;
            sMi[++eMi] = sMx[++eMx] = i;
            while (l < i) {
                int mi = a[sMi[fMi + (sMi[fMi] == l)]];
                int mx = a[sMx[fMx + (sMx[fMx] == l)]];
                if (mx - mi < X)
                    break;
                fMi += sMi[fMi] == l;
                fMx += sMx[fMx] == l;
                l++;
            }
            if (a[sMx[fMx]] - a[sMi[fMi]] >= X)
                cnt[i - l + 1]++, cnt[i + 1]--;
        }
        L = 0;
        for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
        while (cnt[L] < k) L++;
        writeT(X);
        putchar(' ');
        writeT(L);
        putchar('\n');
    }

    return 0;
}
