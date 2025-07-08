#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=(ll)998244353;
//阳奉阴违的数据范围
const int N=2000005;
int len,n,q;
int trie[N][27],e[N],idx;
ll ans,h[27][27];
string s;
char zero='a'-1;

void insert(){
    int p=0;e[p]++;
    for(int i=0;i<len;i++){
        int ne=s[i]-'a'+1;
        if(!trie[p][ne])trie[p][ne]=++idx;
        //其他儿子的字符都是在当前字符插入前插入的
        for(int j=0;j<27;j++){
            if(trie[p][j]){
                //统计ne字符前面j字符的数量
                h[j][ne]+=e[trie[p][j]];
            }
        }
        p=trie[p][ne];
        e[p]++;
    }
}
vector<int>a;
void solve(){
    cin>>n>>q;
    while(n--){
        cin>>s;
        s+=zero;
        len=s.size();
        insert();
    }

    while (q--){
        a.clear();
        cin>>s;
        a.push_back(0);
        for(char i:s){
            a.push_back((i-'a'+1));
        }
        ans=0;
        for(int i=1;i<27;i++){
            for(int j=0;j<i;j++)
                ans+=h[a[i]][a[j]];
        }
        cout<<ans<<endl;
    }


}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T=1;
    // cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}




