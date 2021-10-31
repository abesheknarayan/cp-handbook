struct Cuts
{
  vector<vll> v;
  vll vis;
  ll n;
  vll tin, tout, low;

  Cuts(ll _n)
  {
    n = _n;
    v = vector<vll>(n, vll());
    vis = vll(n, 0);
    tin = vll(n, 0);
    tout = vll(n, 0);
    low = vll(n, INF);
  }

  // returns all bridges of the graph in edge form
  vector<pll> bridges()
  {
    ll num = 0;
    vector<pll> bridge;
    fill(all(vis), 0);
    function<void(ll, ll)> dfs = [&](ll x, ll p) {
      vis[x] = 1;
      tin[x] = num;
      low[x] = num;
      num++;
      for (auto it : v[x])
      {
        if (it == p)
          continue;
        if (vis[it]) // back edge
        {
          low[x] = min(tin[it], low[x]);
        }
        else
        {
          dfs(it, x);
          low[x] = min(low[it], low[x]);
          if (low[it] > tin[x])
          {
            bridge.push_back({x, it});
          }
        }
      }
      tout[x] = num;
    };
    dfs(0, -1);
    return bridge;
  }
  // returns all cut vertices
  vll cutVertex()
  {
    ll num = 0;
    vll cutvs;
    fill(all(vis), 0);
    function<void(ll, ll)> dfs = [&](ll x, ll p) {
      vis[x] = 1;
      ll childs = 0;
      tin[x] = num;
      low[x] = num;
      num++;
      for (auto it : v[x])
      {
        if (it == p)
        {
          continue;
        }
        if (vis[it]) // back edge
        {
          low[x] = min(low[x], tin[it]);
        }
        else
        {
          dfs(it, x);
          low[x] = min(low[x], low[it]);

          if (low[it] >= tin[x] && p != -1)
          {
            cutvs.push_back(x);
          }
          childs++;
        }
      }
      if (p == -1 && childs > 1) // root case
      {
        cutvs.push_back(x);
      }
    };
    for (ll i = 0; i < n; i++)
    {
      if (!vis[i])
        dfs(i, -1);
    }
    sort(all(cutvs));
    auto dis = unique(all(cutvs));
    cutvs.resize(distance(cutvs.begin(), dis));
    return cutvs;
  }
};