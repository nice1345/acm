#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
//#define int long long
#define vec vector
ll mod=(ll)998244353;
const int N=200005;
int mm(char a){
    if(a>='a'&&a<='z')return (int)(a-'a');
    else if(a=='.')return 26;
    else return 27;
}
struct tire{
    int idx=0;
    vector<int> sum;
    vector<int> ne;
    vector<vector<int>>tree;
public:
    tire(){
        for(int i=0;i<28;i++)ne.push_back(0);
        tree.push_back(ne);sum.push_back(0);
    }
    //加单词
    int add(string s){
        int p=0,c=0;
        sum[p]++;
        for(int i=0;i<s.size();i++){
            c= mm(s[i]);
            if(!tree[p][c]){
                tree[p][c]=++idx;
                tree.push_back(ne);
                sum.push_back(1);
                p=tree[p][c];
            }
            else{
                p=tree[p][c];
                sum[p]++;
            }
        }
        return p;
    }
    //减单词
    void dele(string s){
        int p=0,c=0;
        sum[0]--;
        for(int i=0;i<s.size();i++){
            c= mm(s[i]);
            if(sum[tree[p][c]]==1){
                tree[p][c]=0;
                break;
            }
            else{
                p=tree[p][c];
                sum[p]--;
            }
        }
    }
    //找到确认字符串,既是当前单词的前缀,又不能是后面未加入的单词的前缀
    string find(string s){
        int p=0,c=0;
        string res="";
        for(int i=0;i<s.size();i++){
            c= mm(s[i]);
            res+=s[i];
            if(!tree[p][c]){
                break;
            }
            else{
                p=tree[p][c];
            }
        }
        return res;
    }
    //删去前面无用的确认字符串
    void de(string s,int num){
        int p=0,c=0;
        sum[0]-=num;
        for(int i=0;i<s.size();i++){
            c= mm(s[i]);
            p=tree[p][c];
            sum[p]-=num;
        }
    }

}pre,suf;
//看懂题意看这:https://blog.csdn.net/qq_33957603/article/details/127938025
void solve(){
    int n;
    cin>>n;
    vector<string>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        suf.add(a[i]);
    }
    string ad;
    for(int i=0;i<n;i++){
        suf.dele(a[i]);
        ad=suf.find(a[i]);
        int en=pre.add(ad),num=0;
        for(int i=0;i<28;i++)
            if(pre.tree[en][i]){
                num+=pre.sum[pre.tree[en][i]];
                pre.tree[en][i]=0;
            }
        if(num)pre.de(ad,num);
        cout<<pre.sum[0]<<endl;
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    // scanf("%d",&T);
    while(T--){
        solve();
    }

    return 0;
}
