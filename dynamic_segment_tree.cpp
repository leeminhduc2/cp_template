template <class ValueType, class RangeType, ValueType nullvalue>
struct segment_tree // Khai bao se co dang segment_tree<kieu du lieu gia tri, kieu du lieu vi tri> ten_bien()
{
    RangeType l, r;
    ValueType value, lazyvalue;
    bool islazy;
    segment_tree *left_child, *right_child;
    segment_tree(RangeType l, RangeType r) : l(l), r(r)
    {
        left_child = right_child = nullptr;
        value = nullvalue;
        lazyvalue = ValueType(0);
        islazy = 0;
    }
    void set(ValueType setvalue)
    {
        value = setvalue;
        if (l == r)
            return;
        extend();
        left_child->set(setvalue);
        right_child->set(setvalue);
    }
    void extend()
    {
        RangeType mid = l + (r - l) / 2;
        if (left_child == nullptr)
            left_child = new segment_tree(l, mid);
        if (right_child == nullptr)
            right_child = new segment_tree(mid + 1, r);
    }
    void assign(ValueType val)
    {
        // INSERT YOUR CODE HERE
    }
    void lazyAssign(ValueType val)
    {
        // INSERT YOUR CODE HERE
    }
    ValueType merge(ValueType x, ValueType y)
    {
        // INSERT YOUR CODE HERE
    }
    void pushDown()
    {
        if (!islazy)
            return;
        islazy = 0;
        left_child->lazyAssign(lazyvalue);
        left_child->assign(lazyvalue);
        right_child->lazyAssign(lazyvalue);
        right_child->assign(lazyvalue);
    }
    void pushUp()
    {
        value = merge(left_child->value, right_child->value);
    }
    void update(RangeType u, RangeType v, ValueType val)
    {
        if (r < u || v < l)
            return;
        if (u <= l && r <= v)
        {
            lazyAssign(val);
            assign(val);
            return;
        }

        extend();
        pushDown();
        left_child->update(u, v, val);
        right_child->update(u, v, val);
        pushUp();
    }
    ValueType get(RangeType u, RangeType v)
    {
        if (r < u || v < l)
            return nullvalue;
        if (u <= l && r <= v)
            return value;
        extend();
        pushDown();
        return merge(left_child->get(u, v), right_child->get(u, v));
    }
};