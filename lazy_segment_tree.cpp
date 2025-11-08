template <class T>
struct lazy_segment_tree
{
    static constexpr T INF = -1e9;

    vector<T> s, lazy;
    int n;
    lazy_segment_tree(int n, T def = INF) : s(4 * n + 2, def), lazy(4 * n + 2, 0), n(n) {}
    void update(int L, int R, T val)
    {
        update(1, 1, n, L, R, val);
    }
    T query(int L, int R)
    {
        return query(1, 1, n, L, R);
    }

private:
    T f(const T &a, const T &b)
    {
        return max(a, b);
    }
    void pushDown(int id)
    {
        T val = lazy[id];
        lazy[id * 2] += val;
        lazy[id * 2 + 1] += val;
        s[id * 2] += val;
        s[id * 2 + 1] += val;
        lazy[id] = 0;
    }
    void update(int id, int l, int r, int u, int v, T val)
    {
        if (r < u || v < l)
        {
            return;
        }
        if (u <= l && r <= v)
        {
            s[id] += val;
            lazy[id] += val;
            return;
        }
        int mid = (l + r) / 2;
        pushDown(id);
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        s[id] = f(s[id * 2], s[id * 2 + 1]);
    }
    T query(int id, int l, int r, int u, int v)
    {
        if (r < u || v < l)
        {
            return INF;
        }
        if (u <= l && r <= v)
        {
            return s[id];
        }
        pushDown(id);
        int mid = (l + r) / 2;
        return f(query(id * 2, l, mid, u, v), query(id * 2 + 1, mid + 1, r, u, v));
    }
};