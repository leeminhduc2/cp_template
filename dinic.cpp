struct FlowEdge
{
    int u,v;
    long long cap,flow=0;
    FlowEdge(int u,int v,long long cap) : u(u), v(v), cap(cap) {}
};
struct Dinic
{
    int n,m=0;
    vector <FlowEdge> edges;
    vector <vector <int>> g;
    vector <int> level,ptr;
    queue<int> q;
    int s,t;
    Dinic(int n,int s,int t) : n(n),s(s),t(t)
    {
        g.resize(n+5);
        level.resize(n+5);
        ptr.resize(n+5);
    }
    void add_edge(int u,int v,long long w)
    {
        edges.push_back({u,v,w});
        edges.push_back({v,u,0});
        g[u].push_back(m);
        g[v].push_back(m+1);
        m+=2;
    }
    bool bfs()
    {
        while (q.size())
        {
            int u=q.front();
            q.pop();
            for (int id:g[u])
            {
                if (edges[id].cap-edges[id].flow==0) continue;
                if (level[edges[id].v]!=-1) continue;
                level[edges[id].v]=level[u]+1;
                q.push(edges[id].v);
            }
        }
        return (level[t]!=-1);
    }
    long long dfs(int u,long long pushed=1e18)
    {
        if (pushed==0) return 0;
        if (u==t) return pushed;
        for (int& cid=ptr[u]; cid<(int) (g[u]).size(); cid++)
        {
            int id=g[u][cid];
            int v=edges[id].v;
            if (level[u]+1!=level[v]||edges[id].cap-edges[id].flow==0) continue;
            int tr=dfs(v,min(pushed,edges[id].cap-edges[id].flow));
            if (!tr) continue;
            edges[id].flow+=tr;
            edges[id^1].flow-=tr;
            return tr;
        }
        return 0;
    }
    long long flow()
    {
        long long maxflow=0ll;
        while ( true)
        {
            fill(level.begin(),level.end(),-1);
            fill(ptr.begin(),ptr.end(),0);
            level[s]=0;
            q.push(s);
            if (!bfs()) break;
            while (long long pushed=dfs(s)) maxflow+=pushed;
        }
        return maxflow;
    }

};