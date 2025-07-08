#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+1;
const int MM=332;
int st[MM+1][N],jump[MM+1][N];
int a[N],top[MM+1];
/**
 当天还给室友发了一道根号分治的题，当天晚上就遇到了，还没开出来，废物啊我  !!!
 一眼n*n的复杂度，很多都是根分  n*sqrt(n)  n*logn*sqrt(n)
 首先一个二分跳等级我就没想到   废物啊我  !!!
 二分跳等级找到到达i之前的等级，就找到答案了
 k>sqrt(n)  最多跳sqrt(n)次  logn*sqrt(n)
  k><=qrt(n)  暴力枚举
  n*sqrt*log


  二分跳步数已经被hack的死死的，还以为在线的做法已死，原来是我不够抽象
  某天来看这代码，突然想到子序列自动机，就突然想到这个思路，虽然写完我都不知道有啥关系，就很突然

  考虑优化二分
  能量为d时，可以把所有等级大于d的怪兽下标存进二维数组中下标为d的一维数组里
  枚举能量为d，起点为cnt，并且k已知时，只需找到cnt后第k个大于等于d的数的位置也就是下标
  之前把能量为d时，所有等级大于d的怪兽下标存进二维数组中下标为d的一维数组里
  我们要找的位置往前k位的位置，我们只需要知道起点为cnt应该从哪个位置往后找k位即可，
  而这个是很好预处理的，手模就行
  这样二分就被优化到O(1)
  n*sqrt
  内存已经占用到极限了，这里开vector要爆，vector有额外的内存，long long也不能搞

  二分可以搞的，只要把枚举的k弄到1800就行了，然后跳的能量就会小于n/1800，O(n*sqrt(n*log(n)))==O(n*1800)
 * */
int k,id,l,r,n,q,m,d,cnt;
int fight[N],run[N];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    m= min((int)sqrt(n),MM);
    for(int i=1;i<=n;i++)cin>>a[i];
    //枚举的能量不超过m,那这儿应该枚举的k为1~n/m
    for(int i=1;i<=n/m;i++){
        d=1;cnt=0;
        for(int j=1;j<=n;j++){
            if(d<=a[j]){
                if(!fight[j])fight[j]=i;
                cnt++;
                if(cnt==i)cnt=0,d++;
            }
            else run[j]=i;
        }
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            if(a[j]>=i)jump[i][++top[i]]=j;
            st[i][j]=top[i];
        }
    while(q--){
        cin>>id>>k;
        if(fight[id]&&fight[id]<=k)cout<<"YES\n";
        else if(run[id]&& run[id] >= k)cout << "NO\n";
        else{
            cnt=0;d=1;
            while(d<=a[id]){
                cnt=st[d][cnt]+k;
                if(cnt>top[d])break;
                cnt=jump[d][cnt];
                if(cnt>=id)break;
                d++;
            }
            if(d<=a[id]){
                fight[id]=k;
                cout<<"YES\n";
            }
            else{
                run[id]=k;
                cout<<"NO\n";
            }
        }
    }
    return 0;
}

/**
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int a[N], n, q, tr[N], idx = 1, l, r, mid, req[N];

void update(int x, int v){
    while(x < N)
        tr[x] += v, x += (x & -x);
}

int query(int x){
    int res = 0;
    while(x)
        res += tr[x], x -= (x & -x);
    return res;
}

bool check(int x, int v){
    return 1ll * a[x] * v <= query(v);
}

int main(){
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for(int i = 1; i <= n; i++){
        l = 1, r = n;
        while(l < r){
            mid = (l + r) >> 1;
            if(check(i, mid))
                l = mid + 1;
            else
                r = mid;
        }
        update(l, 1), req[i] = l;
    }
    for(int i = 1, x, k; i <= q; i++)
        scanf("%d%d", &x, &k), puts(k < req[x] ? "NO" : "YES");
}

 */




/**
 #include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+5,INF=1e18;
int n,q,a[N],p[N],t[N];
void ad(int x,int v){
    while(x<N)t[x]+=v,x+=(x&-x);
}
int qu(int x){
    int res=0;
    while(x)res+=t[x],x-=(x&-x);
    return res;
}
int ck(int x,int v){
    return a[x]*v<=qu(v);
}
void sv(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1,l,r,mid;i<=n;i++){
        l=1,r=n;
        while(l<r){
            mid=l+r>>1;
            if(ck(i,mid))l=mid+1;
            else r=mid;
        }
        ad(l,1);
        p[i]=l;
    }int x,k;
    while(q--){
        cin>>x>>k;
        if(k<p[x])printf("NO\n");
        else printf("YES\n");
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--)sv();
    return 0;
}
 * */