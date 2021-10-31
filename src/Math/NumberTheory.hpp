struct NT
{

    // returns phi of given number in O(sqrt(n))
    // multiplicative
    ll calc_phi(ll x)
    {
        ll res = x;
        for (ll i = 2; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                while (x % i == 0)
                    x /= i;

                res -= res / i;
            }
        }
        if (x > 1)
        {
            res -= res / x;
        }
        return res;
    }

    // calculates phi from 1 to n in O(nlogn)
    // using guass formula sum(phi(x)) where x|n  = n
    vector<ll> calc_phi_1_to_n(ll n)
    {
        vector<ll> phi(n + 1);
        phi[0] = 0;
        phi[1] = 1;
        for (ll i = 2; i <= n; i++)
        {
            phi[i] = i - 1;
        }
        for (ll i = 2; i <= n; i++)
        {
            for (ll j = 2 * i; j <= n; j += i)
            {
                phi[j] -= phi[i];
            }
        }
        return phi;
    }

    // returns primes till n in O(n)
    vector<ll> liear_sieve(ll n)
    {
        vll primes(n, 1);
    }

    // TODO : Discrete log (Baby step giant step) , primitive roots
};