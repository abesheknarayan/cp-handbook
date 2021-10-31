template <typename T>
struct matrix
{
  T mat[2][2];
  matrix() {}
  void matrix_init(T a, T b, T c, T d)
  {
    mat[0][0] = a;
    mat[0][1] = b;
    mat[1][0] = c;
    mat[1][1] = d;
  }
  matrix operator*(const matrix &b)
  {
    matrix res;
    res.matrix_init(0, 0, 0, 0);
    for (ll i = 0; i < 2; i++)
    {
      for (ll k = 0; k < 2; k++)
      {
        for (ll j = 0; j < 2; j++)
        {
          res.mat[i][k] += (mat[i][j] * b.mat[j][k]);
        }
      }
    }
    return res;
  }
  matrix operator+(const matrix &b)
  {
    matrix res;
    res.matrix_init(0, 0, 0, 0);
    for (ll i = 0; i < 2; i++)
    {
      for (ll j = 0; j < 2; j++)
      {
        res.mat[i][j] = (mat[i][j] + b.mat[i][j]);
      }
    }
    return res;
  }
  matrix operator-(const matrix &b)
  {
    matrix res;
    res.matrix_init(0, 0, 0, 0);
    for (ll i = 0; i < 2; i++)
    {
      for (ll j = 0; j < 2; j++)
      {
        res.mat[i][j] = (mat[i][j] - b.mat[i][j]);
      }
    }
    return res;
  }
  void print()
  {
    for (ll i = 0; i < 2; i++)
    {
      for (ll j = 0; j < 2; j++)
      {
        cout << mat[i][j] << " ";
      }
      cout << "\n";
    }
  }
};

using Mat = matrix<Mint>;

Mat b_expo(Mat a, ll n)
{
  Mat res;
  res.matrix_init(1, 0, 0, 1);
  while (n > 0)
  {
    if (n % 2 == 1)
    {
      res = res * a;
    }
    n /= 2;
    a = a * a;
  }
  return res;
}
