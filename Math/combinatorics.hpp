const int N = 3e5 + 5;
Mint fac[N];

void pre()
{
    fac[0] = 1;
    for (ll i = 1; i < N; i++)
    {
        fac[i] = fac[i - 1] * i;
    }
}

Mint ncrp(ll n, ll r)
{
    if (r == 0)
        return 1;
    if (r > n)
        return 0;
    return (fac[n]) / (fac[r] * fac[n - r]);
}