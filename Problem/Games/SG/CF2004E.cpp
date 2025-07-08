#include<bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
int n,cnt=0;
vector<int>primes;
int sg[N];
void get_primes(int x){
    sg[1]=1;
    for(int i=2;i<x;i++){
        if(!sg[i]){
            primes.emplace_back(i);
            cnt++;
            sg[i]=cnt;
        }
        else if(i%2==0)sg[i]=0;
        else sg[i]=sg[sg[i]];
        for(int j=0;j<cnt&&primes[j]<=x/i;j++){
            sg[primes[j] * i]=primes[j];
            if(i%primes[j]==0)break;
        }
    }
}
//官解写的很清楚
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int _=1;
    get_primes(N);sg[2]=0;
    cin>>_;
    for(int i=1;i<=_;i++){
        cin>>n;
        int ans=0;
        for(int i=0;i<n;i++){
            int ne;cin>>ne;
            ans^=sg[ne];
        }
        cout<<((ans>0)?"Alice":"Bob")<<"\n";
    }
    return 0;
}