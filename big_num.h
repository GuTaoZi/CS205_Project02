#ifndef REMAKE_CALCULATOR_BIG_NUM_H
#define REMAKE_CALCULATOR_BIG_NUM_H

#include "bits/stdc++.h"

#define ll long long

using namespace std;

const regex pure_int("^[+-]?[0-9]+$");
const regex int_with_e("^[+-]?[0-9]+e[+-]?[0-9]+$");
const regex int_with_suffix("^[+-]?[0-9]+[kKmMgGtT]$");
const regex pure_float("^[+-]?[0-9]+.[0-9]+$");
const regex float_with_e("^[+-]?[0-9]+.[0-9]+e[+-]?[0-9]+$");
const regex float_with_suffix("^[+-]?[0-9]+.[0-9]+[kKmMgGtT]$");
const regex abbreviated_float("^[+-]?.[0-9]+$");

const int DIVIDE_PRECISION = 500;

enum data_type
{
    INF, NaN, PURE_INT, INT_WITH_E, INT_WITH_SUFFIX, PURE_FLOAT, FLOAT_WITH_E, FLOAT_WITH_SUFFIX, ABBR_FLOAT
};

// PURE_INT : 19260817
// INT_WITH_E : 1926e0817
// INT_WITH_SUFFIX : 19260817k
// PURE_FLOAT : 1926.0817
// FLOAT_WITH_E : 1926.08e17
// FLOAT_WITH_SUFFIX : 1926.0817k
// ABBR_FLOAT : -.19260817

data_type classifier(string s);


struct BigNum
{
    int len;
    short val[10005];//1e4 digits, from low to high
    bool sign;//true: +
    ll exp;
    data_type type;

    BigNum()
    {
        len = 1;
        memset(val, 0, sizeof(val));
        sign = true;
        exp = 0;
        type = PURE_INT;
    }

    BigNum(string s)
    {
        memset(val, 0, sizeof(val));
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        this->type = classifier(s);
        switch (type)
        {
            case PURE_INT:
            {
                this->sign = true;
                this->exp = 0;
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                }
                for (int i = 1; i <= s.size(); i++)
                {
                    this->val[i] = s[s.size() - i] - '0';
                }
                this->len = s.size();
                break;
            }
            case INT_WITH_E:
            {
                this->sign = true;
                this->exp = 0;
                int pos = s.find('e');
                if (s[pos + 1] == '-')
                {
                    pos++;
                }
                for (int i = pos + 1; i < s.size(); i++)
                {
                    exp *= 10;
                    exp += s[i] - '0';
                }
                if (s[pos] == '-')
                {
                    exp = -exp;
                    pos--;
                }
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                    pos--;
                }
                for (int i = 1; i <= pos; i++)
                {
                    this->val[i] = s[pos - i] - '0';
                }
                this->len = pos;
                break;
            }
            case INT_WITH_SUFFIX:
            {
                this->sign = true;
                switch (s[s.size() - 1])
                {
                    case 'k':
                    {
                        this->exp = 3;
                        break;
                    }
                    case 'm':
                    {
                        this->exp = 6;
                        break;
                    }
                    case 'g':
                    {
                        this->exp = 9;
                        break;
                    }
                    case 't':
                    {
                        this->exp = 12;
                        break;
                    }
                    default:
                    {
                        printf("wrong suffix!\n");
                    }
                }
                s.erase(s.size() - 1, 1);
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                }
                for (int i = 1; i <= s.size(); i++)
                {
                    this->val[i] = s[s.size() - i] - '0';
                }
                this->len = s.size();
                break;
            }
            case PURE_FLOAT:
            {
                int pos = s.find('.');
                this->exp = -(s.size() - pos - 1);
                s.erase(pos, 1);
                this->sign = true;
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                }
                for (int i = 1; i <= s.size(); i++)
                {
                    this->val[i] = s[s.size() - i] - '0';
                }
                this->len = s.size();
                break;
            }
            case FLOAT_WITH_E:
            {
                int dot_pos = s.find('.');
                this->sign = true;
                int e_pos = s.find('e');
                ll base_exp = -(e_pos - dot_pos - 1);
                s.erase(dot_pos, 1);
                e_pos--;
                if (s[e_pos + 1] == '-')
                {
                    e_pos++;
                }
                this->exp = 0;
                for (int i = e_pos + 1; i < s.size(); i++)
                {
                    exp *= 10;
                    exp += s[i] - '0';
                }
                if (s[e_pos] == '-')
                {
                    exp = -exp;
                    e_pos--;
                }
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                    e_pos--;
                }
                for (int i = 1; i <= e_pos; i++)
                {
                    this->val[i] = s[e_pos - i] - '0';
                }
                this->exp += base_exp;
                this->len = e_pos;
                break;
            }
            case FLOAT_WITH_SUFFIX:
            {
                this->exp = 0;
                switch (s[s.size() - 1])
                {
                    case 'k':
                    {
                        this->exp += 3;
                        break;
                    }
                    case 'm':
                    {
                        this->exp += 6;
                        break;
                    }
                    case 'g':
                    {
                        this->exp += 9;
                        break;
                    }
                    case 't':
                    {
                        this->exp += 12;
                        break;
                    }
                    default:
                    {
                        printf("wrong suffix!\n");
                    }
                }
                s.erase(s.size() - 1, 1);
                int pos = s.find('.');
                this->exp += -(s.size() - pos - 1);
                s.erase(pos, 1);
                this->sign = true;
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                }
                for (int i = 1; i <= s.size(); i++)
                {
                    this->val[i] = s[s.size() - i] - '0';
                }
                this->len = s.size();
                break;
            }
            case ABBR_FLOAT:
            {
                this->sign = true;
                this->exp = 0;
                if (s[0] == '-')
                {
                    this->sign = false;
                    s.erase(0, 1);
                }
                s.erase(0, 1);
                for (int i = 1; i <= s.size(); i++)
                {
                    this->val[i] = s[s.size() - i] - '0';
                }
                this->len = s.size();
                this->exp = -this->len;
                break;
            }
            default:
            {
                printf("wrong type!\n");
            }
        }
    }

    BigNum(ll x)
    {
        len=0;
        memset(val, 0, sizeof(val));
        sign=x>0;
        exp=0;
        while(x)
        {
            val[++len]=x%10;
            x/=10;
        }
        type=PURE_INT;
    }
};

//utils
BigNum standardize_exp(BigNum a);

BigNum shorten(BigNum a,int lim);

bool is_zero(BigNum a);

string toString(BigNum a, ll constraint);

BigNum calc(BigNum a, BigNum b, char op);

BigNum calculate(string s);

//operators
BigNum operator+(BigNum a, BigNum b);

BigNum operator-(BigNum a, BigNum b);

BigNum operator*(BigNum a, BigNum b);

BigNum operator/(BigNum a, BigNum b);

BigNum operator-(BigNum a);

bool operator<(BigNum a, BigNum b);

bool operator==(BigNum a, BigNum b);

bool operator>(BigNum a, BigNum b);

bool operator<=(BigNum a, BigNum b);

bool operator>=(BigNum a, BigNum b);

BigNum operator^(BigNum a,BigNum b);

#endif //REMAKE_CALCULATOR_BIG_NUM_H
