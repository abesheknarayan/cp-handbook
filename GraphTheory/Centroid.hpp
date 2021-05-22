struct CentroidDecomp
{
  ll n, k1, k2;
  vector<vll> v;
  vll marked; // for marking already visited centroids
  vll subtreeSize;
  long long ans;
  o_tree tr;
  // segTree sg;
 
  CentroidDecomp(ll _n, ll _k1, ll _k2)
  {
    n = _n;
    k1 = _k1;
    k2 = _k2;
    ans = 0;
    v = vector<vll>(n, vll());
    subtreeSize.assign(n, 1);
    marked.assign(n, 0);
    // sg = segTree(2e5+5);
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
 
      ll maxdep = -1;
      
      // do computations here

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