
struct segTree
{
  ll size;
  vll data; // delta contains operations
  ll neutral;
  vector<pll> intervals;
  segTree() {}
  segTree(ll n)
  {
    size = 1;
    while (size < n)
      size *= 2ll;
    data.assign(2 * size - 1, 0ll); // fill depending on what data stores
    intervals.assign(2 * size - 1, {-1, -1});
    build(vll(n, 0));
    neutral = 0;
  }

  void build(const vll &a, ll node, ll l, ll r)
  {
    intervals[node] = {l, r};
    if (l == r)
    {
      ll indx = node - (2 * size - 1) / 2;
      if (indx >= a.size())
        return;
      data[node] = a[indx];
      return;
    }
    ll mid = l + (r - l) / 2;
    ll left = 2 * node + 1;
    ll right = 2 * node + 2;
    build(a, left, l, mid);
    build(a, right, mid + 1, r);
    update(node);
  }
  void build(const vll &a)
  {
    build(a, 0, 0, size - 1);
  }

  ll op(ll a, ll b) // used in update , query , prop
  {
    return a + b;
  }

  ll op2(ll a, ll b)
  {
    return min(a, b);
  }

  void update(ll node) // update parent
  {
    ll left = 2 * node + 1;
    ll right = 2 * node + 2;
    data[node] = op(data[left], data[right]);
  }

  void modify(ll l, ll r, ll val, ll node, ll lo, ll hi)
  {
    if (l > hi || r < lo)
    {
      return;
    }
    if (l <= lo && r >= hi)
    {
      data[node] = val;
      return;
    }
    ll mid = lo + (hi - lo) / 2;
    modify(l, r, val, 2 * node + 1, lo, mid);
    modify(l, r, val, 2 * node + 2, mid + 1, hi);
    update(node);
  }

  void modify(ll l, ll r, ll val) // set data[indx] = val
  {
    modify(l, r, val, 0, 0, size - 1);
  }

  ll query(ll l, ll r, ll node, ll lo, ll hi)
  {
    if (l > hi || r < lo)
    {
      return 0;
    }
    if (l <= lo && r >= hi)
    {
      return data[node];
    }
    ll mid = lo + (hi - lo) / 2;
    ll left_val = query(l, r, 2 * node + 1, lo, mid);
    ll right_val = query(l, r, 2 * node + 2, mid + 1, hi);
    update(node);
    return op(left_val, right_val);
  }

  ll query(ll l, ll r)
  {
    return query(l, r, 0, 0, size - 1);
  }
};

struct HLD
{
  ll n;
  vector<vll> v;
  vll par, dep, heavy, subsize;
  vll master, index; // master is the combination of all heavy paths, index is mapping
  vll hldhead;
  vll cost;
  segTree sg;

  HLD(ll _n,const vll &a)
  {
    n = _n;
    v = vector<vll>(n, vll());
    par.assign(n, -1);
    dep.assign(n, 0);
    heavy.assign(n, -1);
    subsize.assign(n, 1);
    index.assign(n, -1);
    hldhead.assign(n, -1);
    cost = a;
    sg = segTree(n);
  }

  void addEdge(ll x, ll y)
  {
    v[x].push_back(y);
    v[y].push_back(x);
  }
  /* 
    1. Find heavy nodes and mark dfs
    2. Each node will correspond to atleast one heavy node
    3. Heavy tour to build the whole segment tree vector using another dfs
    4. Works only for static trees
    5. Use int if TLE
  */
  void buildHLD()
  {
    function<void(ll, ll)> dfs = [&](ll x, ll p)
    {
      ll maxi = 0;
      for (auto it : v[x])
      {
        if (it == p)
          continue;
        par[it] = x;
        dep[it] = dep[x] + 1;
        dfs(it, x);
        subsize[x] += subsize[it];
        if (subsize[it] > maxi)
        {
          maxi = subsize[it];
          heavy[x] = it;
        }
      }
    };
    dfs(0, -1);
    ll nowhead = -1;
    function<void(ll, ll)> dfs2 = [&](ll x, ll p)
    {
      master.push_back(x);
      if (heavy[x] == -1) // leaf
      {
        if (p != -1 && heavy[p] == x)
        {
          hldhead[x] = nowhead;
        }
        else
        {
          hldhead[x] = x;
        }
        nowhead = -1;
      }
      else
      {
        if (nowhead == -1)
          nowhead = x;
        hldhead[x] = nowhead;
      }
      if (heavy[x] != -1)
      {
        dfs2(heavy[x], x);
      }
      for (auto it : v[x])
      {
        if (it == p || it == heavy[x])
          continue;
        dfs2(it, x);
      }
    };
    dfs2(0, -1);
    vll finar(n);
    for (ll i = 0; i < n; i++)
    {
      index[master[i]] = i;
      finar[i] = cost[master[i]];
    }
    sg.build(finar);
  }

  /* 1.supports only node update
     2.change segment tree according to this (no need of lazy)
  */
  void update(ll node, ll val)
  {
    ll indx = index[node];
    sg.modify(indx, indx, val);
  }

  ll query(ll a, ll b)
  {
    ll res = 0;
    while (true)
    {
      ll head_a = hldhead[a];
      ll head_b = hldhead[b];
      if (head_a == head_b)
      {
        // both belong to same heavy component
        ll indx_a = index[a];
        ll indx_b = index[b];
        if (indx_a > indx_b)
          swap(indx_a, indx_b);
        res += (sg.query(indx_a, indx_b));
        break;
      }
      else
      {
        if (dep[head_a] > dep[head_b])
        {
          ll indx_1 = index[hldhead[a]];
          ll indx_2 = index[a];
          if (indx_1 > indx_2)
            swap(indx_1, indx_2);
          res += sg.query(indx_1, indx_2);
          a = par[hldhead[a]];
        }
        else
        {
          ll indx_1 = index[hldhead[b]];
          ll indx_2 = index[b];
          if (indx_1 > indx_2)
            swap(indx_1, indx_2);
          res += sg.query(indx_1, indx_2);
          b = par[hldhead[b]];
        }
      }
    }
    return res;
  }
};
