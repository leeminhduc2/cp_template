template <class T> //Khi khai bao can khai bao theo dang fenwick_tree<data type> variable()
struct fenwick_tree
{
    int n;
    vector<T> fen;
    fenwick_tree(int n = 0) : n(n)
    {
        fen.resize(n + 1, 0);
    }
    void update(int pos, T val)
    {
        for (; pos <= n; pos += pos & -pos)
            fen[pos] += val;
    }
    T get(int pos)
    {
        T res = T(0);
        for (; pos > 0; pos -= pos & -pos)
        {
            res += fen[pos];
        }
        return res;
    }
    T get(int l, int r)
    {
        return get(r) - get(l - 1);
    }
};