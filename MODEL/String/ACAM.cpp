#include<bits/stdc++.h>
using namespace std;
vector<int> pu(26,0);
struct ACAM{
    vector<vector<int>>trie;
    vector<int>len,h,id,fail;
    int idx=0,MAXM=26,n;
    int insert(string s) {
        int p = 0;
        for (int i = 0; i < s.length(); i++) {
            int c = s[i] - 'a';
            if (!trie[p][c]) {
                trie[p][c] = ++idx;
                trie.emplace_back(pu);
                h.emplace_back(0);
                len.emplace_back(len[p]+1);
            }
            p = trie[p][c];
        }
        h[p]++;
        return p;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i <MAXM; i++)
            if (trie[0][i])
                q.push(trie[0][i]);
        fail.resize(idx+1);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < MAXM; i++) {
                if (trie[p][i]) {
                    fail[trie[p][i]] = trie[fail[p]] [i];
                    q.push(trie[p][i]);
                }
                else
                    trie[p][i] = trie[fail[p]] [i];
            }
        }
    }
    ACAM(vector<string> &s){
        n=s.size();
        id.resize(n);
        trie.emplace_back(pu);
        h=len={0};
        for(int i=0;i<n;i++)id[i]=insert(s[i]);
        build();
    }
    //写自己的逻辑
    vector<int>sum;
    void init(){sum.resize(idx+1);}
    void query(string s){
        priority_queue<pair<int,int>>q;
        for (int i = 0,p=0; i < s.length(); i++) {
            int c = (s[i] - 'a');
            p = trie[p][c];
            if(!sum[p])q.push({len[p],p});
            sum[p]++;
        }
        map<int,int>pw;
        while(!q.empty()){
            int p=q.top().second;q.pop();
            if(!sum[fail[p]])q.push({len[fail[p]],fail[p]});
            sum[fail[p]]+=sum[p];
            if(h[p])pw[p]=sum[p];
            sum[p]=0;
        }
        for(int i:id)cout<<pw[i]<<"\n";
    }
};
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;vector<string> a(n);
    for(string &i:a)cin>>i;
    ACAM tr(a);
    tr.init();
    string s;cin>>s;
    tr.query(s);
    return 0;
}