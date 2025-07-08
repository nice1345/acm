#include<bits/stdc++.h>
using namespace std;
int T,q,n,tree[3000005][65],e[3000005],idx;
char s[3000005];
int getnum(char x){
    if(x>='A'&&x<='Z')
        return x-'A';
    else if(x>='a'&&x<='z')
        return x-'a'+26;
    else
        return x-'0'+52;
}
void add(char str[]){
    int p=0,len=strlen(str);
    for(int i=0;i<len;i++){
        int c=getnum(str[i]);
        if(!tree[p][c])
            tree[p][c]=++idx;
        p=tree[p][c];
    }
    e[p]++;
}
int query(char str[]){
    int p=0,len=strlen(str);
    for(int i=0;i<len;i++){
        int c=getnum(str[i]);
        if(!tree[p][c])
            return 0;
        p=tree[p][c];
    }
    return e[p];
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            add(s);
        }
        for(int i=1;i<=q;i++){
            scanf("%s",s);
            printf("%d\n",query(s));
        }
        if(T!=0){
            for(int i=0;i<=idx;i++){
                e[i]=0;
                for(int j=0;j<=122;j++)
                    tree[i][j]=0;
            }
            idx=0;
        }
    }
    return 0;
}