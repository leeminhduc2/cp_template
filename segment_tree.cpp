struct segment_tree {
    typedef int T;
    static constexpr T INF = -1e9;
    T f(const T &a, const T &b) {
        return max(a,b);
    }
    vector<T> s;
    int n;
    segment_tree(int n, T def = INF) : s(2 * n + 2, def), n(n) {}
    void update(int pos, T val) {
        // Default : s[pos += n] = val. Change if you wish to
        for (s[pos += n] = val; pos/=2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int L, int R) { // query [L,R)
        T ra = INF, rb = INF;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {
            if (L & 1)
                ra = f(ra, s[L++]);
            if (R & 1)
                rb = f(s[--R], rb);
        }
        return f(ra, rb);
    }
};