struct SCC{
    ll n;
    vector<vll> v,rv;
    ll no_scc;
    vll scc_id;
    vll order;
    stack<ll> st;
    vll vis;
    

    // Kosaraju Alg to find SCCs
    SCC(ll _n)
    {
        n = _n;
        v = vector<vll>(n,vll());
        rv = vector<vll>(n,vll());
        no_scc = 0;
        scc_id.assign(n,-1);
        vis.assign(n,0);
    }

    void dfs1(ll x)
    {
        vis[x]=1;
        for(auto it:v[x])
        {
            if(!vis[it])dfs1(it);
        }
        st.push(x);
    }

    void addEdge(ll x,ll y)
    {
        v[x].push_back(y);
        rv[y].push_back(x);
    }
    

    void dfs2(ll x)
    {
        scc_id[x] = no_scc;
        for(auto it:rv[x])
        {
            if(scc_id[it] == -1)
            dfs2(it);
        }
    }

    vll get_dfs_order()
    {
        return order;
    }

    void get_scc()
    {
        for(ll i=0;i<n;i++)
        {
            if(vis[i])continue;
            dfs1(i);
        }

        while(!st.empty())
        {
            ll x = st.top();
            order.push_back(x);
            st.pop();
            if(scc_id[x]!=-1)continue;
            no_scc++;
            dfs2(x);
        }
    }


};