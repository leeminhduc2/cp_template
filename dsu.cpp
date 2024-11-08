struct dsu{
    int n;
    vector <int> par;
    dsu(int n) : n(n){
        par.resize(n+1);
        for (int i=1;i<=n;i++) par[i]=i;
    }
    int get(int u)
    {
        return (par[u]==u ? u : par[u]=get(par[u]));
    }
    void join(int u,int v)
    {
        u=get(u),v=get(v);
        if (u==v) return;
        if (u>v) swap(u,v);
        par[v]=u;
    }
};