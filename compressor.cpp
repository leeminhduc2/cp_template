template <class T>
struct compressor {
    vector<T> a;
    compressor() {}
    compressor(vector<T> a): a(a) {}
    void compress() {
        sort(all(a));
        a.erase(unique(all(a)),a.end());
    }
    int get(T x) {
        return lower_bound(all(a),x)-a.begin(); // 0-based
    }
    int size() {
        return sz(a);
    }
    void add(T x) {
        a.pb(x);
    }
};