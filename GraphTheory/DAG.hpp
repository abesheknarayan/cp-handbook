struct DAG
{
    ll n;
    vector<vll> v;
    vll vis;
    vll order;
    vll comp;
    vll state;
    stack<ll> st;
    ll hascycle;
    ll noc;

    DAG(ll _n)
    {
        n = _n;
        v = vector<vll>(n, vll());
        vis.assign(n, 0);
        comp.assign(n, -1);
        state.assign(n, 0);
        noc = 0;
        hascycle = false;
    }

    void addEdge(ll x, ll y)
    {
        v[x].push_back(y);
    }
    // 0 - new , 1 in call stack 2 = done
    bool dfs(ll x)
    {
        // cross edge
        if (state[x] == 2)
        {
            return false;
        }
        // back edge
        if (state[x] == 1)
        {
            return true;
        }
        state[x] = 1;
        for (auto it : v[x])
        {
            if (dfs(it))
            {
                return true;
            }
        }
        state[x] = 2;
        st.push(x);
        return false;
    }

    void dfs2(ll x)
    {
        vis[x] = 1;
        comp[x] = noc;
        for (auto it : v[x])
        {
            if (vis[it])
                continue;
            dfs2(it);
        }
    }

    // used dfs but can use Kahns too if we want priority

    void dodfs()
    {
        vis.assign(n, 0);
        for (ll i = 0; i < n; i++)
        {
            if(!vis[i])
            {
                dfs2(i);
                noc++;
            }
        }
        
    }

    vll topsort()
    {
        for (ll i = 0; i < n; i++)
        {
            if (state[i] == 0)
            {
                hascycle |= dfs(i);
            }
        }
        assert(!hascycle);
        while (!st.empty())
        {
            order.push_back(st.top());
            st.pop();
        }
        return order;
    }

    bool samecomp(ll x, ll y)
    {
        return comp[x] == comp[y];
    }
};
