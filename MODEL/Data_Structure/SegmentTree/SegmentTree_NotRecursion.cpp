
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1000005;
ll mod = (ll) 998244353;

template<typename T>
/**
 * 静态结构线段树，所有操作不递归，支持对区间[l,r]的查询，其中1<=l<=r<size
 * @tparam T 结点类型，结点需要支持+运算符
 */
struct SegmentTree {
    int size{};
    vector<T> node;

    SegmentTree() : size(0) {}

    void build(int n) {
        size = 1;
        while (size <= n) size <<= 1;
        vector<T>(size * 2).swap(node);// 清空并缩/扩容
    }

    void build(const vector<T> &arr) {
        build(arr.size() - 1);
        ///把数组铺在底层,注意线段树里数组下标从1开始. arr[0]必须无用
        copy(arr.begin() + 1, arr.end(), node.begin() + size + 1);
        for (int i = size - 1; i > 0; i--) {
            node[i] = node[i * 2] + node[i * 2 + 1];
        }
    }

    void modify(int idx, const T &v) {
        assert(0 < idx && idx < size);
        idx += size;
        node[idx] = v;
        while (idx > 1) {
            idx >>= 1;
            node[idx] = node[idx * 2] + node[idx * 2 + 1];
        }
    }

    T &get(int idx) {
        return node[idx + size];
    }

    T query(int l, int r) {
        assert(0 < l && r < size);
        l += size - 1;
        r += size + 1;
        T lans{}, rans{};
        for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1) lans = lans + node[l ^ 1];
            if (r & 1) rans = node[r ^ 1] + rans;
        }
        return lans + rans;
    }

    void print() { //打印树结构
        int j = 1, s = size * 4, k, len = 3;///len：每个要输出的数值的长度
        for (int i = 1; i <= 2 * size - 1; i++) {
            if (i == j) {
                cout << endl;
                j <<= 1;
                s >>= 1;
                for (k = 0; k < len * (s / 2 - 1); k++)
                    cout << " ";
            }
            cout << setw(len) << node[i];
            for (k = 0; k < len * (s - 1); k++)
                cout << " ";
        }
        cout << endl;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}
