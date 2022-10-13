#include "big_num.h"
#include <bits/stdc++.h>

using namespace std;

bool operator<(BigNum a, BigNum b)//抛开符号比大小
{
    a = standardize_exp(a);
    b = standardize_exp(b);
    if ((a.exp + a.len) == (b.exp + b.len))
    {
        if (a.len >= b.len)
        {
            for (int i = 0; i < b.len; i++)
            {
                if (a.val[a.len - i] != b.val[b.len - i])
                {
                    return a.val[a.len - i] < b.val[b.len - i];
                }
            }
            return false;
            //抹零后比较，若b位数已经比完，说明后面都是0了，a肯定不小于b
        }
        else
        {
            for (int i = 0; i < a.len; i++)
            {
                if (a.val[a.len - i] != b.val[b.len - i])
                {
                    return a.val[a.len - i] < b.val[b.len - i];
                }
            }
            return true;
            //抹零后比较，若a位数已经比完，说明后面都是0了，a肯定小于b
        }
    }
    else
    {
        return ((a.exp + a.len) < (b.exp + b.len));
    }
}

BigNum operator*(BigNum a, BigNum b)
{
    a = standardize_exp(a);
    b = standardize_exp(b);
    BigNum c;
    c.exp = a.exp + b.exp;
    c.sign = !(a.sign xor b.sign);
    c.len = a.len + b.len + 1;
    if (a < b)
    {
        swap(a, b);
    }
    for (int i = 1; i <= a.len; i++)
    {
        for (int j = 1; j <= b.len; j++)
        {
            c.val[i + j - 1] += a.val[i] * b.val[j];
        }
    }
    for (int i = 1; i <= c.len; i++)
    {
        if (c.val[i] >= 10)
        {
            c.val[i + 1] += c.val[i] / 10;
            c.val[i] %= 10;
            c.len = max(c.len, i + 1);
        }
    }
    c = standardize_exp(c);
    return c;
}

BigNum operator+(BigNum a, BigNum b)
{
    a = standardize_exp(a);
    b = standardize_exp(b);
    BigNum c;
    if (a.sign)
    {
        if (b.sign)
        {
            c.sign = true;
        }
        else
        {
            return a - b;
        }
    }
    else
    {
        if (b.sign)
        {
            return b - a;
        }
        else
        {
            c.sign = false;
        }
    }
    if (a < b)
    {
        swap(a, b);
    }
    c.exp = b.exp;
    if (a.exp - b.exp >= b.len)
    {
        for (int i = 1; i <= b.len; i++)
        {
            c.val[++c.len] = b.val[i];
        }
        for (int i = b.len + 1; i <= a.exp - b.exp; i++)
        {
            c.val[++c.len] = 0;
        }
        for (int i = 1; i <= a.len; i++)
        {
            c.val[++c.len] = a.val[i];
        }
    }//毫无进位
    else
    {
        for (int i = 1; i <= a.exp - b.exp; i++)
        {
            c.val[++c.len] = b.val[i];
        }
        for (int i = 1; i <= a.len; i++)
        {
            c.val[++c.len] = a.val[i] + b.val[a.exp - b.exp + i];
        }//b高位默认0
        for (int i = 1; i <= c.len; i++)
        {
            if (c.val[i] >= 10)
            {
                c.val[i + 1]++;
                c.val[i] -= 10;
            }
        }
        if (c.val[c.len + 1])
        {
            c.len++;
        }
    }
    c = standardize_exp(c);
    return c;
}

bool operator==(BigNum a, BigNum b)
{
    if (a < b || b < a)
    {
        return false;
    }
    return true;
}

BigNum operator-(BigNum a)
{
    BigNum b = a;
    b.sign = !b.sign;
    return b;
}

BigNum operator-(BigNum a, BigNum b)
{
    a = standardize_exp(a);
    b = standardize_exp(b);
    BigNum c = BigNum();
    if (a.sign)
    {
        if (b.sign)
        {
            c.sign = b < a;
        }
        else
        {
            b.sign = true;
            return a + b;
        }
    }
    else
    {
        if (b.sign)
        {
            b.sign = false;
            return a + b;
        }
        else
        {
            a.sign = true;
            b.sign = true;
            return b - a;
        }
    }
    if (a < b)
    {
        return -(b - a);
    }
    else if (a == b)
    {
        return BigNum();
    }
    else
    {
        if (a.exp >= b.exp)//a后补0
        {
            c.sign = true;
            c.exp = b.exp;
            c.len = a.len + a.exp - b.exp;
            for (int i = 1; i <= a.len; i++)
            {
                c.val[i + a.exp - b.exp] = a.val[i];
            }
            int borrow = 0;
            for (int i = 1; i <= c.len; i++)//给a补0
            {
                if (c.val[i] < borrow + b.val[i])
                {
                    c.val[i] = c.val[i] + 10 - borrow - b.val[i];
                    borrow = 1;
                }
                else
                {
                    c.val[i] -= borrow + b.val[i];
                    borrow = 0;
                }
            }
            c = standardize_exp(c);
            return c;
        }
        else//b后补0
        {
            c.sign = true;
            c.exp = a.exp;
            c.len = a.len;
            for (int i = 1; i <= c.len; i++)
            {
                c.val[i] = a.val[i];
            }
            int borrow = 0;
            for (int i = 1; i <= b.len; i++)
            {
                if (c.val[i + b.exp - a.exp] < borrow + b.val[i])
                {
                    c.val[i + b.exp - a.exp] = c.val[i + b.exp - a.exp] + 10 - borrow - b.val[i];
                    borrow = 1;
                }
                else
                {
                    c.val[i + b.exp - a.exp] -= borrow + b.val[i];
                    borrow = 0;
                }
            }
            c = standardize_exp(c);
            return c;
        }
    }
}

BigNum operator/(BigNum a, BigNum b)
{
    if(is_zero(b))
    {
        BigNum err=BigNum();
        err.type= is_zero(a)?NaN:INF;
        return err;
    }
    BigNum c = BigNum();
    c.sign=!(a.sign xor b.sign);
    a.sign=b.sign= true;
    c.exp=a.exp-b.exp;
    c.len=0;
    int expa=a.exp;
    int expb=b.exp;
    a.exp=0;
    b.exp=0;
    if(a<b)//扩大a直到a>b
    {
        while(a<b)
        {
            //printf("%d--\n",a.exp);
            a.exp++;
            c.exp--;
        }
    }
    else
    {
        b.exp++;
        if(b<a)//缩小a直到a<10b;
        {
            while(b<a)
            {
                //printf("%d--\n",a.exp);
                a.exp--;
                c.exp++;
            }
        }
        b.exp--;
    }//现在是10b>a>b的情况
    while(c.len<DIVIDE_PRECISION)
    {
        int q=0;
        while(!(a<b))
        {
            a=a-b;
            q++;
            a= standardize_exp(a);
        }
        printf("q:%d\n",q);
        c.val[++c.len]=q;
        a.exp++;
        a= standardize_exp(a);
        c.exp--;
        if(is_zero(a)) break;
    }
    c.exp++;
    for(int i=1;i<=(c.len>>1);i++)
    {
        swap(c.val[i],c.val[c.len-i+1]);
    }
    return c;
}