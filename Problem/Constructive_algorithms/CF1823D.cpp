/**
长度为3,本质不同的回文串至少为3,每增加一个字符,本质不同的回文串只会增加0或1;
k<20;把条件分成不同的区间;
每个区间用本质不同的字符填充,多的位置用a,b,c填充,
 例如:1~5有5个,1~8有7个
 1~5:abcdd 6~8:eea
 1~8:abcddeea
 要注意连续字符的两侧的abc不能形成回文串
 例如:1~5有5个,1~8有5个
 1~5:abcdd 6~8:cab
 1~8:abcddcab
 cddc又会形成新的回文串
 要让dd两边的“abc”不相等如:abcddabc
 * */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
int T,n,k,ne,st,cnt,sum;
char no;
char nn[3];
int main() {
    nn[0]='a';nn[1]='b';nn[2]='c';
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&k);
        vector<int>a(n+1);
        vector<int>b(k);
        vector<int>c;
        vector<char>ans;
        for(int i=0;i<k;i++)scanf("%d",&b[i]);
        for(int i=0;i<k;i++)scanf("%d",&a[b[i]]);
        //sort(b.begin(),b.end());
        for(int i=0;i<k;i++){
            if(i<(k-1)&&a[b[i]]==a[b[i+1]])continue;
            c.push_back(b[i]);
        }
        st=-1;cnt=c.size();
        bool h= false;
        if(cnt>0&&a[c[0]]>c[0])h= true;
        for(int i=1;i<cnt;i++){
            sum=a[c[i]]-a[c[i-1]];
            if(sum>(c[i]-c[i-1])||sum<0){
                h= true;
                break;
            }
        }
        if(h){
            puts("NO");
            continue;
        }
        for(int i=0;i<cnt;i++){
            if(c[i]<3)continue;
            st=i;break;
        }
        ans.push_back('a');
        ans.push_back('b');
        ans.push_back('c');
        no='d';
        if(st==-1){
            for(int i=3;i<n;i++)ans.push_back('a');
            puts("YES");
            for(int i=0;i<n;i++)putchar(ans[i]);
            puts("");
            continue;
        }
        sum=a[c[st]]-3;
        for(int i=3;i<(3+sum);i++){
            ans.push_back(no);
        }
        int ii=0;
        if(nn[(sum+3)%3]==nn[2])ii++;
        for(int i=(3+sum);i<c[st];i++){
            ans.push_back(nn[(i+ii)%3]);
        }
        no++;st++;
        for(;st<cnt;st++){
            sum=a[c[st]]-a[c[st-1]];
            for(int i=c[st-1];i<(c[st-1]+sum);i++){
                ans.push_back(no);
            }
            ii=0;
            if(nn[(c[st-1]+sum)%3]==ans[(c[st-1]-1)])ii++;
            for(int i=(c[st-1]+sum);i<c[st];i++){
                ans.push_back(nn[(i+ii)%3]);
            }
            no++;
        }
        for(int i=c[st-1];i<n;i++){
            ans.push_back(nn[i%3]);
        }
        puts("YES");
        for(int i=0;i<n;i++)putchar(ans[i]);
        puts("");
    }

    return 0;
}
