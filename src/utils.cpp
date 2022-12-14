#include "big_num.h"
#include "varia.h"
#include <bits/stdc++.h>

using namespace std;

const string type_name[] = {"NaN", "PURE_INT", "INT_WITH_E", "INT_WITH_SUFFIX", "PURE_FLOAT", "FLOAT_WITH_E",
                            "FLOAT_WITH_SUFFIX", "ABBR_FLOAT"};

BigNum shorten(BigNum a, int lim)
{
    if (a.len <= lim)
    {
        return a;
    }
    int dif = a.len - lim;
    for (int i = 1; i <= lim; i++)
    {
        a.val[i] = a.val[i + dif];
    }
    for (int i = lim + 1; i <= a.len; i++)
    {
        a.val[i] = 0;
    }
    a.exp += dif;
    a.len = lim;
    return a;
}

BigNum standardize_exp(BigNum a)
{
    if (is_zero(a))
    {
        return BigNum();
    }
    BigNum c;
    c.type = PURE_INT;
    c.len = 0;
    c.sign = a.sign;
    c.exp = a.exp;
    for (int i = 1; i <= a.len; i++)
    {
        if (a.val[i] == 0 && c.len == 0)
        {
            c.exp++;
        }
        else
        {
            c.val[++c.len] = a.val[i];
        }
    }
    while (c.val[c.len] == 0)
    {
        c.len--;
    }
    if (c.exp)
    {
        c.type = INT_WITH_E;
    }
    return c;
}

string to_string(BigNum a, ll constraint)
{
    if (a.type == INF)
    {
        return a.sign ? "INF" : "-INF";
    }
    if (a.type == NaN)
    {
        return "NaN";
    }
    string res = "";
    a = standardize_exp(a);
    bool flg = false;
    ll cnt = 0;
    for (int i = a.len; i >= 1; i--)
    {
        if (a.val[i] != 0 || flg)
        {
            cnt++;
            if (constraint != -1 && cnt <= constraint + 1)
            {
                flg = true;
                if (cnt == constraint + 1 && (i > 1 && a.val[i - 1] >= 5))
                {
                    res = res + (char) (a.val[i] + '1');
                }
                else
                {
                    res = res + (char) (a.val[i] + '0');
                }
            }
            else if (constraint == -1)
            {
                res = res + (char) (a.val[i] + '0');
                flg = true;
            }
        }
    }
    if (!flg)
    {
        res = res + "0";
    }
    if (res!="0" && (res.size() > 1 || a.exp))
    {
        ll new_exp = a.exp + cnt - 1;
        if (res.size() > 1)
        {
            res.insert(1, 1, '.');
        }
        if (new_exp)
        {
            res += "e";
            stringstream ss;
            string tmp_s;
            ss.clear();
            ss << new_exp;
            res = res + ss.str();
            ss.clear();
        }
    }
    if (!a.sign)
    {
        res = "-" + res;
    }
    return res;
}

data_type classifier(string s)
{
    if (regex_match(s, pure_int))
    {
        return PURE_INT;
    }
    else if (regex_match(s, int_with_e))
    {
        return INT_WITH_E;
    }
    else if (regex_match(s, int_with_suffix))
    {
        return INT_WITH_SUFFIX;
    }
    else if (regex_match(s, pure_float))
    {
        return PURE_FLOAT;
    }
    else if (regex_match(s, float_with_e))
    {
        return FLOAT_WITH_E;
    }
    else if (regex_match(s, abbreviated_float))
    {
        return ABBR_FLOAT;
    }
    else if (regex_match(s, float_with_suffix))
    {
        return FLOAT_WITH_SUFFIX;
    }
    else
    {
        return NaN;
    }
}

string type_of(string s)
{
    return type_name[classifier(s)];
}

bool is_zero(BigNum a)
{
    for (int i = 1; i <= a.len; i++)
    {
        if (a.val[i])
        {
            return false;
        }
    }
    return true;
}

double to_double(BigNum a)
{
    double res=0;
    a=standardize_exp(shorten(a,200));
    for(int i=1;i<=a.len;i++)
    {
        res*=10;
        res+=a.val[i];
    }
    if(a.exp<0)
    {
        for(int i=1;i<=-a.exp;i++)
        {
            res/=10;
        }
    }
    else
    {
        for(int i=1;i<=a.exp;i++)
        {
            res*=10;
        }
    }
    return res;
}

BigNum to_BigNum(double x)
{
    stringstream ss;
    ss<<setprecision(15)<<x;
    return BigNum(ss.str());
}