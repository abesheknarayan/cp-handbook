struct CentroidDecomp{
  ll n;
  vector<vll> v;
  vll subtreeSize;

  CentroidDecomp(ll _n)
  {
    n = _n;
    v = vector<vll>(n,vll());
    subtreeSize.assign(n,1);
  }

  void addEdge(ll x,ll y)
  {
    v[x].push_back(y);
    v[y].push_back(x);
  }

  ll findCentroid()
  {
    ll centroid = -1;
    
    // returns size of subtree
    function<void(ll,ll)> dfs1 = [&](ll x,ll p)
    {
      bool ok = true;
      for(auto it:v[x])
      {
        if(it == p)continue;
        dfs1(it,x);
        subtreeSize[x]+=subtreeSize[it];
        if(subtreeSize[it] > n/2)
        {
          ok = false;
        }
      }
      if(subtreeSize[x] < n/2) ok = false;
      if(ok)
      {
        centroid = x;
      }
    };
    dfs1(0,-1);
    assert(centroid!=-1);
    return centroid;
  }
};