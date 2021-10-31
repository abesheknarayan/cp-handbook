struct DSU
{
  // rank heuristical DSU
  ll n, noc;
  vll par, siz, rank;

  DSU(ll N)
  {
    n = N, noc = N;
    par.assign(N, 1);
    siz.assign(N, 1);
    rank.assign(N, 1);
    for (ll i = 0; i < N; i++)
    {
      par[i] = i;
    }
  }
  ll get(ll x)
  {
    return par[x] = (par[x] == x ? x : get(par[x]));
  }
  bool sameset(ll x, ll y)
  {
    return get(x) == get(y);
  }
  void join(ll x, ll y)
  {
    x = get(x);
    y = get(y);
    if (x != y)
    {
      noc--;
      if (rank[x] >= rank[y])
      {
        if (rank[x] == rank[y])
          rank[x]++;
        // unite y with x
        par[y] = x;
        siz[x] += siz[y];
      }
      else
      {
        // unite x with y
        par[x] = y;
        siz[y] += siz[x];
      }
    }
  }

  ll no_comp()
  {
    return noc;
  }
  ll size_of_comp(ll x)
  {
    return siz[get(x)];
  }
};