#ifndef ATCODER_LAZYSEGTREE_HPP
#define ATCODER_LAZYSEGTREE_HPP 1

#include <algorithm>  // 包含标准算法函数
#include <cassert>    // 包含断言宏，用于调试检查
#include <iostream>   // 包含输入输出流
#include <vector>     // 包含向量容器

// 计算不小于 n 的最小 2 的幂次（用于确定线段树大小）
// 参数 n: 原始数组大小
// 返回值: 满足 2^x >= n 的最小 x
int ceil_pow2(int n) {
    // 处理 n=0 或 n=1 的特殊情况
    if (n <= 1) return 0;

    int x = 0;  // 幂指数计数器
    // 循环直到找到最小的 x 使得 2^x >= n
    // 使用无符号整数防止位移溢出
    while ((1U << x) < (unsigned int)(n)) {
        x++;
    }
    return x;
}



// 定义节点数据类型：值+区间长度
struct S {
    long long value;
    int len;
};

// 合并两个节点（求和）
S op(S a, S b) {
    return {a.value + b.value, a.len + b.len};
}

// 单位元（空节点）
S e() {
    return {0, 0};
}

// 修改操作：区间加（用long long存储加数）
using F = long long;
// 修改操作单位元（无操作）
F id() {
    return 0;
}

// 应用修改：区间加 => value += f * len
S mapping(F f, S s) {
    if (f == id()) return s; // 无修改
    return {s.value + f * s.len, s.len}; // 关键：乘以区间长度
}

// 合并修改：先加g，再加f => 等价于加(f+g)
F composition(F f, F g) {
    return f + g;
}


namespace atcoder {
// ======================== 惰性传播线段树模板 ========================
// 模板参数说明:
// S: 节点数据类型（存储线段树节点信息）
// op: 合并两个节点的函数 (S, S) -> S（必须满足结合律）
// e: 返回S类型单位元的函数 () -> S（满足 op(a, e()) = a）
// F: 修改操作类型（表示对区间的修改）
// mapping: 应用修改到节点的函数 (F, S) -> S（将修改应用到节点数据）
// composition: 合并两个修改操作的函数 (F, F) -> F（必须满足结合律）
// id: 返回F类型单位元的函数 () -> F（满足 mapping(id(), s) = s）
    template <class S,
            S (*op)(S, S),
            S (*e)(),
            class F,
            S (*mapping)(F, S),
            F (*composition)(F, F),
            F (*id)()>
    struct lazy_segtree {
    private:
        int _n;            // 原始数组大小
        int size;          // 线段树实际大小（2的幂）
        int log;           // 树的高度（log2(size)）
        std::vector<S> d;  // 存储线段树节点数据（索引从1开始，大小为2*size）
        std::vector<F> lz; // 存储懒标记（仅非叶子节点需要，大小为size）

        // 更新节点：根据两个子节点计算父节点值
        // 参数 k: 当前节点索引（从1开始）
        void update(int k) {
            // 使用op函数合并左右子节点（索引为2k和2k+1）
            d[k] = op(d[2 * k], d[2 * k + 1]);
        }

        // 对节点应用修改操作
        // 参数 k: 当前节点索引
        // 参数 f: 要应用的修改操作
        void all_apply(int k, F f) {
            // 使用mapping函数将修改f应用到节点k的数据
            d[k] = mapping(f, d[k]);
            // 如果是非叶子节点（k < size），更新懒标记
            if (k < size) {
                // 使用composition函数合并新标记和旧标记
                // 注意: 这里假设修改操作满足结合律
                lz[k] = composition(f, lz[k]);
            }
        }

        // 下推懒标记到子节点
        // 参数 k: 当前节点索引
        void push(int k) {
            // 将当前节点的懒标记应用到左右子节点
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            // 重置当前节点懒标记为单位元
            lz[k] = id();
        }

    public:
        // ======================== 构造函数 ========================
        // 默认构造函数（创建空线段树）
        lazy_segtree() : lazy_segtree(0) {}

        // 创建大小为n的线段树，所有节点初始化为e()
        explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}

        // 使用给定向量初始化线段树
        explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
            // 计算树的高度（log2(n)的上界）
            log = ceil_pow2(_n);
            // 计算实际线段树大小（2的log次幂）
            size = 1 << log;
            // 初始化节点数据：2*size个元素，初始值为e()
            d.assign(2 * size, e());
            // 初始化懒标记：size个元素，初始值为id()
            lz.assign(size, id());

            // 复制初始数据到叶子节点（位置从size到size+_n-1）
            for (int i = 0; i < _n; i++) {
                d[size + i] = v[i];
            }

            // 自底向上构建线段树（从最后一个非叶子节点开始）
            // 注意：索引从size-1递减到1（根节点）
            for (int i = size - 1; i >= 1; i--) {
                update(i);
            }
        }

        // ======================== 基本操作 ========================
        // 单点设置：将位置p的值设为x
        // 参数 p: 位置索引（0 ≤ p < _n）
        // 参数 x: 新值
        void set(int p, S x) {
            // 检查索引有效性
            assert(0 <= p && p < _n);
            // 转换为叶子节点索引
            p += size;
            // 从根到叶子下推路径上的所有懒标记
            for (int i = log; i >= 1; i--) {
                push(p >> i);  // 下推当前层级的标记
            }
            // 设置叶子节点值
            d[p] = x;
            // 从叶子到根更新所有祖先节点
            for (int i = 1; i <= log; i++) {
                update(p >> i);  // 更新当前层级的节点
            }
        }

        // 单点查询：获取位置p的值
        // 参数 p: 位置索引（0 ≤ p < _n）
        S get(int p) {
            assert(0 <= p && p < _n);
            p += size;
            // 下推路径上的懒标记
            for (int i = log; i >= 1; i--) {
                push(p >> i);
            }
            // 返回叶子节点值
            return d[p];
        }

        // 区间查询：查询区间 [l, r) 的值（左闭右开）
        // 参数 l: 左边界（包含）
        // 参数 r: 右边界（不包含）
        S prod(int l, int r) {
            // 检查边界有效性
            assert(0 <= l && l <= r && r <= _n);
            // 空区间返回单位元
            if (l == r) return e();

            // 转换为线段树索引
            l += size;
            r += size;

            // 下推左右边界路径上的懒标记
            for (int i = log; i >= 1; i--) {
                // 检查左边界是否是该层的最左点
                if (((l >> i) << i) != l) push(l >> i);
                // 检查右边界是否是该层的最右点
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }

            // 初始化左右累加器
            S sml = e(), smr = e();
            // 自底向上遍历线段树
            while (l < r) {
                // 如果l是右子节点，直接处理并右移
                if (l & 1) sml = op(sml, d[l++]);
                // 如果r是右子节点，先左移再处理
                if (r & 1) smr = op(d[--r], smr);
                // 上移到父层
                l >>= 1;
                r >>= 1;
            }

            // 合并左右结果
            return op(sml, smr);
        }

        // 查询整个区间 [0, _n)
        S all_prod() {
            // 直接返回根节点（索引1）
            return d[1];
        }

        // 单点修改：对位置p应用修改f
        // 参数 p: 位置索引
        // 参数 f: 修改操作
        void apply(int p, F f) {
            assert(0 <= p && p < _n);
            p += size;
            // 下推路径上的懒标记
            for (int i = log; i >= 1; i--) push(p >> i);
            // 应用修改到叶子节点
            d[p] = mapping(f, d[p]);
            // 更新祖先节点
            for (int i = 1; i <= log; i++) update(p >> i);
        }

        // 区间修改：对区间 [l, r) 应用修改f（左闭右开）
        // 参数 l: 左边界（包含）
        // 参数 r: 右边界（不包含）
        // 参数 f: 修改操作
        void apply(int l, int r, F f) {
            // 检查边界有效性
            assert(0 <= l && l <= r && r <= _n);
            // 空区间直接返回
            if (l == r) return;

            // 转换为线段树索引
            l += size;
            r += size;

            // 下推左右边界路径上的懒标记
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }

            {
                // 保存原始边界（用于后续更新）
                int l2 = l, r2 = r;
                // 自底向上应用修改
                while (l < r) {
                    // 如果l是右子节点，直接应用并右移
                    if (l & 1) all_apply(l++, f);
                    // 如果r是右子节点，先左移再应用
                    if (r & 1) all_apply(--r, f);
                    // 上移到父层
                    l >>= 1;
                    r >>= 1;
                }
                // 恢复原始边界值
                l = l2;
                r = r2;
            }

            // 更新受影响的祖先节点
            for (int i = 1; i <= log; i++) {
                // 更新左边界路径
                if (((l >> i) << i) != l) update(l >> i);
                // 更新右边界路径
                if (((r >> i) << i) != r) update((r - 1) >> i);
            }
        }

        // ======================== 二分搜索操作 ========================
        // 二分查找：从l开始的最右位置，使区间[l, x)满足条件g
        // 模板参数 g: 条件函数（bool(S)）
        // 参数 l: 起始位置
        // 返回值: 满足条件的最大x
        template <bool (*g)(S)> int max_right(int l) {
            // 将函数指针转换为函数对象
            return max_right(l, [](S x) { return g(x); });
        }

        // 通用二分查找（支持函数对象）
        // 参数 l: 起始位置
        // 参数 g: 条件函数对象（bool(S)）
        template <class G> int max_right(int l, G g) {
            // 检查边界有效性
            assert(0 <= l && l <= _n);
            // 单位元必须满足条件
            assert(g(e()));
            // 如果从末尾开始，直接返回_n
            if (l == _n) return _n;

            // 转换为线段树索引
            l += size;
            // 下推路径上的懒标记
            for (int i = log; i >= 1; i--) push(l >> i);

            // 初始化累加器
            S sm = e();
            do {
                // 跳过左子节点（向上直到遇到右子节点）
                while (l % 2 == 0) l >>= 1;

                // 检查当前节点是否不满足条件
                if (!g(op(sm, d[l]))) {
                    // 向下查找满足条件的边界
                    while (l < size) {
                        push(l);  // 下推懒标记
                        l = (2 * l);  // 移动到左子节点
                        // 检查左子节点是否满足条件
                        if (g(op(sm, d[l]))) {
                            // 满足则累加并移动到右子节点
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    // 返回原始坐标
                    return l - size;
                }
                // 累加当前节点值
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);  // 直到l是2的幂次（到达新层级）

            return _n;  // 整个区间都满足条件
        }

        // 二分查找：到r结束的最左位置，使区间[x, r)满足条件g
        // 模板参数 g: 条件函数（bool(S)）
        // 参数 r: 结束位置
        // 返回值: 满足条件的最小x
        template <bool (*g)(S)> int min_left(int r) {
            return min_left(r, [](S x) { return g(x); });
        }

        // 通用二分查找（支持函数对象）
        // 参数 r: 结束位置
        // 参数 g: 条件函数对象（bool(S)）
        template <class G> int min_left(int r, G g) {
            assert(0 <= r && r <= _n);
            assert(g(e()));
            if (r == 0) return 0;
            r += size;
            // 下推路径上的懒标记
            for (int i = log; i >= 1; i--) push((r - 1) >> i);

            S sm = e();
            do {
                r--;
                // 跳过右子节点（向上直到遇到左子节点）
                while (r > 1 && (r % 2)) r >>= 1;

                // 检查当前节点是否不满足条件
                if (!g(op(d[r], sm))) {
                    // 向下查找满足条件的边界
                    while (r < size) {
                        push(r);
                        r = (2 * r + 1);  // 移动到右子节点
                        // 检查右子节点是否满足条件
                        if (g(op(d[r], sm))) {
                            // 满足则累加并移动到左子节点
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                // 累加当前节点值
                sm = op(d[r], sm);
            } while ((r & -r) != r);  // 直到r是2的幂次

            return 0;  // 整个区间都满足条件
        }
    };

}  // namespace atcoder

#endif  // ATCODER_LAZYSEGTREE_HPP

using namespace std;
using namespace atcoder;
int main() {
    // 初始化数组 [1, 3, 2, 5, 4]
    vector<S> init = {
            {1, 1}, {3, 1}, {2, 1}, {5, 1}, {4, 1}
    };

    // 创建线段树
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);

    // 查询[0, 5) => 1+3+2+5+4 = 15
    cout << "Initial sum: " << seg.prod(0, 5).value << endl;

    // 区间加: [1, 4) 每个元素加+2 (即下标1,2,3)
    seg.apply(1, 4, 2);
    // 数组变为 [1, 5, 4, 7, 4]

    // 查询[0, 3) => 1+5+4 = 10
    cout << "Sum [0,3): " << seg.prod(0, 3).value << endl;

    // 查询[2, 5) => 4+7+4 = 15
    cout << "Sum [2,5): " << seg.prod(2, 5).value << endl;

    // 单点查询: 位置3 (值=7)
    cout << "Point 3: " << seg.get(3).value << endl;
}