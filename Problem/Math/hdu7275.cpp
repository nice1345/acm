#include <bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=(int)3e5+5;
ll mod=(long)1e9+7;
int t,n,m,q,w,a1,b1,a2,b2;
int last[N*2],go[N*2],now[N],f[N],cnt;
set<int>myson[N];
ll qmi(ll a,ll b){
    ll res=1,p=a;
    while (b){
        if(b&1)res=res*p%mod;
        p=p*p%mod;
        b>>=1;
    }
    return res;
}

void add(int u,int v){
    last[++cnt]=now[u];
    now[u]=cnt;
    go[cnt]=v;
    // cout<<last[cnt]<<" "<<now[u]<<" "<<go[cnt]<<" "<<u<<" "<<v<<endl;
}

void dfs(int fa,int no){
    // cout<<"1"<<endl;
    myson[no].insert(no);
    for(int i=now[no];i>0;i=last[i]){
        int so=go[i];
        if(so==fa)continue;
        //  cout<<no<<so<<i<<endl;
        dfs(no,so);
        for(int j:myson[so]){
            myson[no].insert(j);
        }
    }
}
vector<int>ans1;
vector<int>ans2;
vector<int>st;
vector<int>en;
vector<int>an1;
vector<int>an2;
void find(int fa,int no,int end,vector<int> &ai){
    if(no==end)return;
    int so;
    for(int i=now[no];i;i= last[i]){
        so=go[i];
        if(so==fa)continue;
        if(myson[so].contains(end)){
            ai.push_back(so);
            find(no,so,end,ai);
            break;
        }
    }
}

void query(int str,int end,vector<int> &aim,int no,int fa){
//    st.clear();
//    en.clear();
    int ls=0,le=0,so;
    for(int i=now[no];i;i= last[i]){
        so=go[i];
        if(so==fa)continue;
        if(myson[so].contains(str))ls=so;
        if(myson[so].contains(end))le=so;
    }
    if(ls==le){
        query(str,end,aim,ls,no);
        return;
    }
    else if(ls==0||le==0){
        en.push_back(no);
        if(ls==0){
            find(fa,no,end,en);
        } else{
            find(fa,no,str,st);
        }
    }
    else{
        en.push_back(no);
        find(fa,no,end,en);
        find(fa,no,str,st);
    }
    int l=st.size();
    for(int i=l-1;i>=0;i--){
        aim.push_back(st[i]);
    }
    l=en.size();
    for(int i=0;i<l;i++){
        aim.push_back(en[i]);
    }
}

int gcd(int a,int b){return b?gcd(b,b%a):a;}
int exgcd(int a,int b,int &x,int &y){
    int d=a; if(b==0) x=1,y=0; else{
        d=exgcd(b,a%b,y,x),y-=a/b*x;
    }
    return d;
}
//unordered_set<int>gc[N*3];
map<pair<int,int>,vector<int>>gc;
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n+5;i++)myson[i].clear();
    for(int i=1;i<n+5;i++)now[i]=0;
    cnt=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&q,&w);
        add(q,w);
        add(w,q);
    }

    dfs(0,1);

//    for(int i=1;i<=len;i++){
//        for(int j:myson[i])printf("%d ",j);
//        printf("\len");
//    }

    // return;
    printf("\n");
    while (m--){
        scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
        if(a1==a2){
            printf("%d\n",a1);
            continue;
        }
        ans1.clear();
        ans2.clear();
        st.clear();
        en.clear();
        query(a1,b1,ans1,1,0);

        st.clear();
        en.clear();
        query(a2,b2,ans2,1,0);
        int l1=ans1.size(),l2=ans2.size();
        an1.clear();an2.clear();
       // unordered_set<int>qc;
        for(int i=0;i<l1;i++){
            an1.push_back(ans1[i]);
            //qc.insert(ans1[i]);
        }
        for(int i=l1-2;i>=0;i--){
            an1.push_back(ans1[i]);
        }
        for(int i=0;i<l2;i++){
            an2.push_back(ans2[i]);
            //qc.insert(ans2[i]);
        }
        for(int i=l2-2;i>=0;i--){
            an2.push_back(ans2[i]);
        }

//        for(int i:an1)printf("%d ",i);
//        printf("\len");
//        for(int i:an2)printf("%d ",i);
//        printf("\len");
        l1=an1.size()-1;l2=an2.size()-1;
        int x,y,gon= exgcd(l1,l2,x,y);
        gon= abs(gon);
        //for(int i=0;i<gon;i++)gc[i].clear();
        gc.clear();
        for(int i=1;i<=l1;i++){
            pair<int,int>vi;
            vi.first=i%gon;
            vi.second=an1[i];
            gc[vi].push_back(i);
           // gc[i%gon].insert(an1[i]);
        }
        bool hhh= true;
        int pw=-1,ml=2147483647;
        for(int i=1;i<=l2;i++){
            pair<int,int>vi;
            vi.first=i%gon;
            vi.second=an2[i];
            for(int j:gc[vi]){
                  int nl=x*(i-j)/gon;
                  nl=(nl%(l2/gon)+l2/gon)%(l2/gon);
                  nl=nl*l1+j;
                //printf("%d %d %d %d\len",nl,an2[i],i,j);

                  if(nl<ml){
                      ml=nl;
                      pw=an2[i];
                  }
            }

//            if(gc[i%gon].contains(an2[i])){
//                printf("%d\len",an2[i]);
//                hhh= false;
//                break;
//            }
        }
        //if(hhh)  printf("-1\len");
        printf("%d\n",pw);
    }
}
int main() {
  //  freopen("1001.in", "r", stdin); //设置 cin scanf 这些输入流都从 test01.in
    scanf("%d",&t);
    //t=1;
    while (t--){
        solve();
    }
    return 0;
}


