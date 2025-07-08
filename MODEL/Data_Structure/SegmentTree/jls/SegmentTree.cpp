#include <bits/stdc++.h>

using i64 = long long;
template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

constexpr int inf = 1E9;
struct Info {
    int ans = inf;
    int cnt = 0;
    int pre = inf;
    int suf = inf;
};

Info operator+(Info a, Info b) {
    Info c;
    c.ans = std::min({a.ans, b.ans, a.pre + b.suf});
    c.cnt = a.cnt + b.cnt;
    c.pre = std::min(a.pre - b.cnt, b.pre);
    c.suf = std::min(a.suf, b.suf - a.cnt);
    return c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::array<int, 2>> A(N * M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x;
            std::cin >> x;
            A[i * M + j] = {x, j};
        }
    }
    std::sort(A.begin(), A.end(), std::greater());

    SegmentTree<Info> seg(M);
    for (int i = 0; i < M; i++) {
        seg.modify(i, {inf, 0, -std::max(0, i - K + 1) + 1, std::min(i, M - K)});
    }
    std::vector<int> cnt(M);
    i64 ans = 0;
    for (auto [v, i] : A) {
        cnt[i]++;
        seg.modify(i, {std::min(i, M - K) - std::max(0, i - K + 1) + 1 - cnt[i], cnt[i], -std::max(0, i - K + 1) + 1 - cnt[i], std::min(i, M - K) - cnt[i]});
        if (seg.rangeQuery(0, M).ans < 0) {
            cnt[i]--;
            seg.modify(i, {std::min(i, M - K) - std::max(0, i - K + 1) + 1 - cnt[i], cnt[i], -std::max(0, i - K + 1) + 1 - cnt[i], std::min(i, M - K) - cnt[i]});
        } else {
            ans += v;
        }
    }
    std::cout << ans << "\n";

    return 0;
}