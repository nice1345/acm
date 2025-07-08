#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1000005; // 最大节点数
const int MAXM = 26; // 字符集大小

int trie[MAXN][MAXM]; // Trie树
int fail[MAXN]; // 失败指针
int cnt[MAXN]; // 模式串出现次数
int idx = 0; // Trie树节点计数器

int du[MAXN];
int insert(string s) {
    int p = 0;int d=0;
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        if (!trie[p][c]) trie[p][c] = ++idx;
        p = trie[p][c];
        du[p]=++d;
    }
    cnt[p]=1;
    return p;
}

void build() {
    queue<int> q;
    for (int i = 0; i < MAXM; i++)
        if (trie[0][i])
            q.push(trie[0][i]);


    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < MAXM; i++) {
            if (trie[p][i]) {
                //子节点的失配指针指向父节点的失配节点的该类子节点或失配子节点
                fail[ trie[p][i] ] = trie[ fail[p] ] [i];
                q.push(trie[p][i]);
            } else
                //没有该类子节点就指向失配节点的该类子节点或失配子节点
                trie[p][i] = trie[ fail[p] ] [i];

        }
    }
}
int ans[MAXN];
struct cmp{
    bool operator () (int a,int b){
        return (du[a]<du[b]);
    }
};
priority_queue<int,vector<int>,cmp>queue1;
void query(string s) {
    int p = 0;
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        p = trie[p][c];
        if(!ans[p])queue1.push(p);
        ans[p]++;
    }
    while(!queue1.empty()){
        int no=queue1.top();
        queue1.pop();
        if(!ans[fail[no]])queue1.push(fail[no]);
        ans[fail[no]]+=ans[no];
    }
}
string sss;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int>ind(n);
    for (int i = 0; i < n; i++) {
        cin >> sss;
        ind[i]= insert(sss);
    }
    build();
    string t;
    cin >> t;
    query(t);
    for(int i=0;i<n;i++)
        cout<<ans[ind[i]]<<endl;

    return 0;
}