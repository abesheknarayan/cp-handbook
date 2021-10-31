struct segTree
{
  ll size;
  vll data, delta; // delta contains operations
  ll neutral;
  vector<pll> intervals;
  segTree(ll n)
  {
    size = 1;
    while (size < n)
      size *= 2ll;
    data.assign(2 * size - 1, 0ll); // fill depending on what data stores
    delta.assign(2 * size - 1, 0ll);
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
    data[node] = op2(data[left] + delta[left], data[right] + delta[right]);
  }

  void prop(ll node)
  {
    ll left = 2 * node + 1;
    ll right = 2 * node + 2;
    // operation here depends on what we modify
    delta[left] += delta[node];
    delta[right] += delta[node];
    delta[node] = 0;
  }

  void modify(ll l, ll r, ll val, ll node, ll lo, ll hi)
  {
    if (l > hi || r < lo)
    {
      return;
    }
    if (l <= lo && r >= hi)
    {
      delta[node] += val;
      return;
    }
    ll mid = lo + (hi - lo) / 2;
    if (lo != hi)
    {
      prop(node);
    }
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
      return INF;
    }
    if (l <= lo && r >= hi)
    {
      return data[node] + delta[node];
    }
    if (lo != hi)
    {
      prop(node);
    }
    ll mid = lo + (hi - lo) / 2;
    ll left_val = query(l, r, 2 * node + 1, lo, mid);
    ll right_val = query(l, r, 2 * node + 2, mid + 1, hi);
    update(node);
    return op2(left_val, right_val);
  }

  ll query(ll l, ll r)
  {
    return query(l, r, 0, 0, size - 1);
  }
};