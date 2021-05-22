struct CentroidDecomp
{
  ll n;
  vector<vll> v;
  vll marked; // for marking already visited centroids
  vll subtreeSize;
  long long ans;
  vector<vector<pll>> levelCentroids;

  CentroidDecomp(ll _n)
  {
    n = _n;
    ans = 0;
    v = vector<vll>(n, vll());
    subtreeSize.assign(n, 1);
    marked.assign(n, 0);
    levelCentroids = vector<vector<pll>>(n, vector<pll>());
  }

  void addEdge(ll x, ll y)
  {
    v[x].push_back(y);
    v[y].push_back(x);
  }

  ll getCentroid(ll node)
  {
    function<void(ll, ll)> get_subsize = [&](ll x, ll p)
    {
      subtreeSize[x] = 1;
      for (auto it : v[x])
      {
        if (it == p || marked[it])
          continue;
        get_subsize(it, x);
        subtreeSize[x] += subtreeSize[it];
      }
    };
    get_subsize(node, -1);
    function<ll(ll, ll)> dfs = [&](ll x, ll p)
    {
      for (auto it : v[x])
      {
        if (it == p || marked[it])
          continue;
        if (subtreeSize[it] > subtreeSize[node] / 2)
        {
          return dfs(it, x);
        }
      }
      return x;
    };
    return dfs(node, -1);
  }

  void decompose_graph()
  {
    function<void(ll)> decompose = [&](ll x)
    {
      ll centroid_now = getCentroid(x);
      marked[centroid_now] = 1;

      // do computations here

      levelCentroids[centroid_now].push_back({centroid_now, 0});

      function<void(ll, ll, ll)> compute = [&](ll xx, ll p, ll dep)
      {
        levelCentroids[xx].push_back({centroid_now, dep});
        for (auto it : v[xx])
        {
          if (it == p || marked[it])
            continue;
          compute(it, xx, dep + 1);
        }
      };

      for (auto it : v[centroid_now])
      {
        if (marked[it])
          continue;
        compute(it, -1, 1);
      }

      for (auto next : v[centroid_now])
      {
        if (!marked[next])
        {
          decompose(next);
        }
      }
      marked[centroid_now] = 0;
    };
    decompose(0);
  }
};