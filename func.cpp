#include "bits/stdc++.h"
#include "big_num.h"
#include "functions.h"

using namespace std;

const int PRECISION = 100;

BigNum exp(BigNum a)
{
    //cout<<"exp";
    if (is_zero(a))
    {
        return BigNum(1);
    }
    if (a.type == INF || a.type == NaN)
    {
        return a;
    }
    BigNum res = BigNum(1);
    BigNum fac = BigNum(1);
    for (int i = 1; i <= PRECISION; i++)
    {
        //cout<<i<<": "<<toString(res,-1);
        BigNum it = BigNum(i);
        fac = fac * it;
        res = res + ((a ^ it) / fac);
    }
    return res;
}

BigNum ln(BigNum a)
{
    //cout<<"ln\n";
    if (a == BigNum(1))
    {
        return BigNum(0);
    }
    if (!a.sign || is_zero(a))
    {
        BigNum err = BigNum();
        err.type = NaN;
        return err;
    }
    BigNum res = BigNum();
    BigNum t = shorten((a - BigNum(1)) / (a + BigNum(1)), 100);
    //cout << "t: " << toString(t, -1)<<endl;
    for (int i = 1; i <= 2 * PRECISION; i++)
    {
        if (i & 1)
        {
            //cout << i << ": " << toString(res, -1) << endl;
            BigNum it = BigNum(i);
            //cout << "t^it: " << toString(t ^ it, -1) << endl;
            res = res + BigNum(2) / it * shorten(t ^ it, 40);
            res = shorten(res, 40);
        }
    }
    return res;
}

BigNum sin(BigNum a)
{

}

BigNum cos(BigNum a)
{

}