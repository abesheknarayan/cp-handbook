
// TODO : Prop and update , kinda confusing 
struct segTree2D
{
  ll n, m;
  ll rowsize, colsize;
  vector<vll> mat;
  vector<vll> rowseg, delta;

  segTree2D(ll _n, ll _m)
  {
    n = _n;
    m = _m;
    rowsize = 1;
    colsize = 1;
    while (rowsize < _n)
      rowsize *= 2;
    while (colsize < _m)
      colsize *= 2;
    mat = vector<vll>(n, vll(m, 0));
    rowseg = vector<vll>(2 * rowsize - 1, vll(2 * colsize - 1, 0ll));
    delta = vector<vll>(2 * rowsize - 1, vll(2 * colsize - 1, 0ll));
  }

  ll op(ll a, ll b)
  {
    return a + b;
  }

  void build_y(ll nodex, ll lx, ll rx, ll nodey, ll ly, ll ry)
  {
    if (ly == ry)
    {
      if (lx == rx)
      {
        // single element
        ll x_indx = nodex - (2 * rowsize - 1) / 2;
        ll y_indx = nodey - (2 * colsize - 1) / 2;
        if (x_indx >= n || y_indx >= m)
          return;

        rowseg[nodex][nodey] = mat[x_indx][y_indx];
      }
      else
      {
        // its a column from lx to rx
        ll left = nodex * 2 + 1;
        ll right = nodex * 2 + 2;
        rowseg[nodex][nodey] = op(rowseg[left][nodey], rowseg[right][nodey]);
      }
    }
    else
    {
      ll y_mid = ly + (ry - ly) / 2;
      ll left_y = 2 * nodey + 1;
      ll right_y = 2 * nodey + 2;
      build_y(nodex, lx, rx, left_y, ly, y_mid);
      build_y(nodex, lx, rx, right_y, y_mid + 1, ry);
      rowseg[nodex][nodey] = op(rowseg[nodex][left_y], rowseg[nodex][right_y]);
    }
  }

  void build_x(ll nodex, ll lx, ll rx)
  {
    if (lx != rx)
    {
      ll mid = lx + (rx - lx) / 2;
      build_x(2 * nodex + 1, lx, mid);
      build_x(2 * nodex + 2, mid + 1, rx);
    }
    build_y(nodex, lx, rx, 0, 0, colsize - 1);
  }

  void build(const vector<vll> &a)
  {
    mat = a;
    build_x(0, 0, rowsize - 1);
  }

  void modify_y(ll nodex, ll nodey, ll ly, ll ry, ll y_lo, ll y_hi, ll val)
  {
    if (ly > y_hi || ry < y_lo)
    {
      return;
    }
    if (ly <= y_lo && ry >= y_hi)
    {
      return rowseg[nodex][nodey] += val;
    }
    // prop here
    ll y_mid = y_lo + (y_hi - y_lo) / 2;
    modify_y(nodex, nodey * 2 + 1, ly, ry, y_lo, y_mid, val);
    modify_y(nodex, nodey * 2 + 2, ly, ry, y_mid + 1, y_hi, val);
    // update here
    rowseg[nodex][nodey] = op(rowseg[nodex][nodey*2+1],rowseg[nodex][nodey*2+2]);
  }

  void modify_x(ll nodex, ll lx, ll rx, ll ly, ll ry, ll x_lo, ll x_hi, ll val)
  {
    if (lx > x_hi || rx < x_lo)
    {
      return;
    }
    if (lx <= x_lo && rx >= x_hi)
    {
      return modify_y(nodex, 0, ly, ry, 0, colsize - 1, val);
    } 
    // prop here
    ll x_mid = x_lo + (x_hi - x_lo) / 2;
    modify_x(2 * nodex + 1, lx, rx, ly, ry, x_lo, x_mid, val);
    modify_x(2 * nodex + 2, lx, rx, ly, ry, x_mid + 1, x_hi, val);
    // update here
  }

  void modify(ll lx, ll rx, ll ly, ll ry, ll val)
  {
    modify_x(0, lx, rx, ly, ry, 0, rowsize - 1, ll val);
  }

  ll query_y(ll nodex, ll nodey, ll ly, ll ry, ll y_lo, ll y_hi)
  {
    if (ly > y_hi || ry < y_lo)
    {
      return 0;
    }
    if (ly <= y_lo && ry >= y_hi)
    {
      return rowseg[nodex][nodey];
    }
    // prop here

    ll y_mid = y_lo + (y_hi - y_lo) / 2;
    ll leftval = query_y(nodex, 2 * nodey + 1, ly, ry, y_lo, y_mid);
    ll rightval = query_y(nodex, 2 * nodey + 2, ly, ry, y_mid + 1, y_hi);
 
    // update here
    rowseg[nodex][nodey] = op(rowseg[nodex][2*nodey+1],rowseg[nodex][2*nodey+2]);

    return op(leftval, rightval);
  }

  ll query_x(ll nodex, ll lx, ll rx, ll ly, ll ry, ll x_lo, ll x_hi)
  {
    if (lx > x_hi || rx < x_lo)
    {
      return 0;
    }
    if (lx <= x_lo && rx >= x_hi)
    {
      return query_y(nodex, 0, ly, ry, 0, colsize - 1);
    }
    // prop here
    ll x_mid = x_lo + (x_hi - x_lo) / 2;
    ll leftval = query_x(2 * nodex + 1, lx, rx, ly, ry, x_lo, x_mid);
    ll rightval = query_x(2 * nodex + 2, lx, rx, ly, ry, x_mid + 1, x_hi);
    // update here
    return op(leftval, rightval);
  }

  ll query(ll lx, ll rx, ll ly, ll ry)
  {
    return query_x(0, lx, rx, ly, ry, 0, rowsize - 1);
  }
};