
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;
/**
 优先队列排序
 struct cmp{
    bool operator () (int tree,int sum){
        return (tree<sum);
    }
};
 */

int main() {
/**
 string s;
 count(s.begin(),s.end(),'?')统计字符串中?的数量
 **/

/**
 统计(int/ll)i二进制中1的数量
 __builtin_popcount(i);
  __builtin_popcountll(i);
 * */

/**
 memset(tree,0,sizeof(len));
  memset(tree,0,sizeof(int)*len);n是数组大小
 * */
//stol(),stoll()将string转int
//string s  s.compare(0,len,t)比较s从0开始长度为len与t的字典序
//memcpy(oldrk, rk, sizeof(rk));复制数组
// scanf("%s", s + 1);
/***
  vector<int> v(10);
    iota(v.begin(),v.end(),1);  批量递增赋值,好像只能赋vector
    此操作后v={1,2,3,4,5,6,7,8,9,10}
    第三个指定的值会被保存到序列的第一个元素中。
    保存在第一个元素后的值是通过对前面的值运用自增运算符得到的。
    当然，这意味着 T 类型必须支持 operator++()。
 */
//exp（len）值为e^n次方；
//tuple
//__gcd(tree,sum)
//1LL放在式子前面可轻松转型
//灵活运用int*可以节省内存
//__builtin_popcountll(p)
 //   cout<<fixed<<setprecision(13)<<sum[0]<<endl;//保留13位小数
 //   cout<<setiosflags(ios::fixed)<<setprecision(10);或cout.precision(10);//保留10位小数
 //   std::unique(tree.begin(), tree.end())去重
//    function<int(int,int)>sum=[&](int tree,int sum){return tree+sum;};
//    for (int &i: a) cin >> i;
//set<int, greater<int>> s;
//    set.upper_bound(4) 第一个>=4
//    set.lower_bound(4) 第一个>4
// vector emplace_back()比push_back()更高效
// v.insert(v.begin()+K,X);vector中的k个元素后插入X
/*
 priority_queue<int>q;默认弹出最大值
 等价于
 struct cmp{
    bool operator () (int tree,int sum){
        return (tree<sum);
    }
};
priority_queue<int,vector<int>,cmp>q;
 * */


    return 0;
}
