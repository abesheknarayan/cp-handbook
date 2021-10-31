const int N = 2e5+5;
vll fin(N,0);
vll aux(N,0);

void addbit(ll bno,ll no)
{
    ll sum = fin[bno] + no;
    ll carry = sum/26;
    ll rem = sum%26;
    // debug(bno,sum,carry,rem);
    if(rem == 0)
    {
        carry--;
        rem = 26;
    }
    fin[bno] = rem;
    if(carry != 0)
    {
        addbit(bno+1,carry);
    }
}

void dividefin(ll bit)
{
    if(bit == -1)return;
    ll no = fin[bit];
    if(no%2==0)
    {
        no/=2;
        fin[bit] = no;
    }
    else{
        ll no2 = 13*no;
        fin[bit] = 0;
        aux[bit-1] = no2;
    }
    dividefin(bit-1);
}