struct Cuts
{
  vector<vll> v;
  vll vis;
  vll tin, tout, low;

  Cuts(ll n)
  {
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
  }
};