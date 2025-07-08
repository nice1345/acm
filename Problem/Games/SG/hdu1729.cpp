#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;
#define in freopen("in.txt", "r", stdin);
typedef long long ll;
const int inf = 0x3f3f3f3f;
/**
 题解：https://www.cnblogs.com/ACMerszl/p/9572948.html
 这递归函数的理解可以根据代码推到和观察该题SG的规律来理解
 * */
int SG(int si, int ci) {
    int q = sqrt((double) si);
    while(q+q*q >= si) q--;//找到刚好使 q+q*q < si && (q+1)+(q+1)*(q+1) >= si
    if(ci > q)    // 先手获胜
        return si - ci;
    else //无法判断，递归
        return SG(q, ci);
}
int main() {
    int n, si, ci;
    int j = 1;
    while(~scanf("%d", &n) && n) {
        int sum = 0;
        while(n--) {
            scanf("%d %d", &si, &ci);
            sum ^= SG(si, ci);
        }
        printf("Case %d:\n", j++);
        if(sum)//原来这里写反了 很郁闷
            printf("Yes\n");
        else
            printf("No\n");
    }
}