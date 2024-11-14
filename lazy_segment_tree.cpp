/** Lazy Segment Tree with large intervals
 *  change value type, lazy type, range type in BOTH TWO STRUCTS and operation functions to implement different operations
*/
struct lazy_segment_tree_node {
    typedef int valueType;
    typedef int lazyType;
    typedef int rangeType;
private:
    static constexpr valueType DEF = -1e9;
public:
    lazy_segment_tree_node *l = nullptr, *r = nullptr;
    
    rangeType lo, hi; // [lo,hi]
    lazyType mset, madd;
    valueType value;
    bool pending_mset;

    lazy_segment_tree_node(rangeType lo,rangeType hi) : lo(lo), hi(hi), mset(0), madd(0), value(0), l(nullptr), r(nullptr), pending_mset(0) {}
    lazy_segment_tree_node(const vector<valueType>& v,rangeType lo,rangeType hi) : lo(lo), hi(hi), mset(0), madd(0), value(0), l(nullptr), r(nullptr), pending_mset(0) {
        if (lo == hi) {
            value = v[lo];
            return;
        }
        rangeType mid = lo + (hi - lo) / 2;
        l = new lazy_segment_tree_node(v,lo,mid);
        r = new lazy_segment_tree_node(v,mid+1,hi);
        value = f(l->value, r->value);
    }

    valueType query(rangeType L,rangeType R) {
        if (R < lo || hi < L) return DEF;
        if (L <= lo && hi <= R) return value;
        pushDown();
        return f(l->query(L,R), r->query(L,R));
    }

    void set(rangeType L,rangeType R, lazyType x) {
        if (R < lo || hi < L) return;
        if (L <= lo && hi <= R) {
            // Change theses lines to implement different lazy update operations
            mset = x;
            madd = 0;
            pending_mset = 1;
            value = x;
            return;
        }
        pushDown();
        l->set(L,R,x);
        r->set(L,R,x);
        value = f(l->value, r->value);
    }

    void add(rangeType L,rangeType R,lazyType x) {
        if (R < lo || hi < L) return;
        if (L <= lo && hi <= R) {
            // Change theses lines to implement different lazy update operations
            if (pending_mset == 0) {
                madd += x;
            } else {
                mset += x;
            }
            value += x;
            return;
        }
        pushDown();
        l->add(L,R,x);
        r->add(L,R,x);
        value = f(l->value, r->value);
    }

    void pushDown() {
        if (l == nullptr) {
            rangeType mid = lo + (hi - lo) / 2;
            l = new lazy_segment_tree_node(lo,mid);
            r = new lazy_segment_tree_node(mid+1,hi);
        }
        if (pending_mset) {
            l->set(lo,hi,mset);
            r->set(lo,hi,mset);
            pending_mset = 0;
        } else if (madd) {
            l->add(lo,hi,madd);
            r->add(lo,hi,madd);
            madd = 0;
        }
    }

    valueType f(valueType a,valueType b) {
        // Change this line to implement different query and update operations
        return max(a,b);
    }

};

struct lazy_segment_tree {
    typedef int valueType;
    typedef int lazyType;
    typedef int rangeType;
    lazy_segment_tree_node *root = nullptr;
    lazy_segment_tree(const vector<valueType>& v) {
        root = new lazy_segment_tree_node(v,0,sz(v)-1);
    }

    lazy_segment_tree(rangeType lo, rangeType hi) {
        root = new lazy_segment_tree_node(lo,hi);
    }

    valueType query(rangeType L,rangeType R) {
        return root->query(L,R);
    }

    void set(rangeType L,rangeType R,lazyType x) {
        root->set(L,R,x);
    }

    void add(rangeType L,rangeType R,lazyType x) {
        root->add(L,R,x);
    }
};