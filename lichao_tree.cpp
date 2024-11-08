struct Line
{
    long long a,b;
    Line(long long a,long long b) : a(a),b(b) {}
    long long operator()(const long long x)
    {
        return a*x+b;
    }
};
struct lichaotree
{
    lichaotree *left,*right;
    long long l,r,m;
    Line d;
    lichaotree(long long l,long long r) : l(l),r(r),d(0ll,1e18) {
        this->m=this->l+(this->r-this->l+1)/2;
        this->left=nullptr;
        this->right=nullptr;
    }
    void add(Line newline)
    {
        bool okl=this->d(this->l)>=newline(this->l),okr=this->d(this->r)>=newline(this->r);
        if (okl&&okr)
        {
            this->d=newline;
            return;
        }
        else if (okl||okr)
        {
            if (this->left==nullptr) this->left=new lichaotree(this->l,this->m);
            if (this->right==nullptr) this->right=new lichaotree(this->m+1,this->r);
            this->left->add(newline);
            this->right->add(newline);
        }
    }
    long long query(long long x)
    {
        if (this->l==this->r) return this->d(x);
        long long res=this->d(x);
        if(x<=this->m&&this->left!=nullptr) res=min(res,this->left->query(x));
        if (x>this->m&&this->right!=nullptr) res=min(res,this->right->query(x));
        return res;
    }
};