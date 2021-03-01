struct LCA
{
    ll n;
    vll vis,par,dep;
    vector<vll> v,table; // adj , ancestor table
 
    LCA(ll _n)
    {
        n = _n;
        vis.assign(n,0ll);
        par.assign(n,-1ll);
        dep.assign(n,0ll);
        v = vector<vll>(n,vll{});
        table = vector<vll>(25,vll(n,-1));
    }

    void dfs(ll x, ll depp)
    {
        vis[x] = 1;
        dep[x] = depp;
        for (auto it : v[x])
        {
            if (!vis[it])
            {
                par[it] = x;
                dfs(it, depp + 1);
            }
        }
    }

    //	table	for	LCA
    void buildLCA()
    {
        ll i, j;
        for (i = 0; i < n; i++)
        {
            table[0][i] = par[i];
        }
        ll lg2 = log2(n);
        for (i = 1; i <= 20; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (table[i - 1][j] != -1)
                {
                    table[i][j] = table[i - 1][table[i - 1][j]];
                }
                else
                {
                    table[i][j] = -1;
                }
            }
        }
    }
    ll findKthAncestor(ll u, ll k)
    {
        ll cur = u;
        ll i;
        for (i = 20; i >= 0; i--)
        {
            if ((1ll << i) & k)
            {
                if (cur == -1)
                {
                    return -1;
                }
                cur = table[i][cur];
            }
        }
        return cur;
    }

    ll getLCA(ll x, ll y)
    {
        if (dep[x] > dep[y])
        {
            ll dif = dep[x] - dep[y];
            x = findKthAncestor(x, dif);
        }
        else if (dep[y] > dep[x])
        {
            ll dif = dep[y] - dep[x];
            y = findKthAncestor(y, dif);
        }

        if (x == y)
        {
            return x;
        }
        ll fdep = dep[x];
        ll l = 1, r = fdep + 5;
        ll fans = -1;
        while (l <= r)
        {
            ll mid = l + (r - l) / 2;
            ll node1 = findKthAncestor(x, mid);
            ll node2 = findKthAncestor(y, mid);
            if (node1 == node2)
            {
                fans = node1;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return fans;
    }

    ll getdis(ll x, ll y)
    {
        ll lca = getLCA(x, y);
        return dep[x] + dep[y] - 2 * dep[lca];
    }
};