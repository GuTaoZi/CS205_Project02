#include "big_num.h"
#include "varia.h"
#include "functions.h"
#include <bits/stdc++.h>

using namespace std;

BigNum calc(BigNum a, BigNum b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return a ^ b;
        default:
        {
            BigNum err = BigNum();
            err.type = NaN;
            return err;
        }
    }
}

void trim(string &s)
{
    int index = 0;
    if (!s.empty())
    {
        while ((index = s.find(' ', index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

bool is_operator(char ch)
{
    switch (ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

const string function_name[] = {"cos", "sin", "exp", "ln","sqrt"};

bool is_func(const string &name)
{
    for (const string &i: function_name)
    {
        if (name == i)
        {
            return true;
        }
    }
    return false;
}

int priority(const string &op)
{
    if (op == "+" || op == "-")
    {
        return 1;
    }
    if (op == "*" || op == "/")
    {
        return 2;
    }
    if (op == "^")
    {
        return 3;
    }
    if (is_func(op))
    {
        return 4;
    }
    return -1;
}

struct aUtO//just kidding :)
{
    BigNum v;
    string s;
    bool is_num;

    aUtO(BigNum v)
    {
        this->v = v;
        is_num = true;
    }

    aUtO(string s)
    {
        this->s = s;
        is_num = false;
    }

    aUtO()
    {
        this->s = "";
        is_num = false;
    }
};

BigNum calculate(string s)
{
    trim(s);
    //cout << "trim: " << s << endl;
    vector<string> sub;
    string it = "";
    for (char i: s)
    {
        if (is_operator(i)&&!(it[it.length()-1]=='e'&&i=='-'))
        {
            if (it != "")
            {
                sub.push_back(it);
                it="";
            }
            sub.push_back(string(1,i));
        }
        else
        {
            it += string(1,i);
        }
    }
    if(it!="")
    {
        sub.push_back(it);
        it="";
    }
    queue<aUtO> q;
    stack<aUtO> stk;
    for (string i: sub)
    {
        if (i.length() == 1 && is_operator(i[0]))
        {
            //this is a operator/brace
            if (i == "(")
            {
                //printf("Left brace detected.\n");
                stk.push(aUtO(i));
                continue;
            }
            else if (i == ")")
            {
                //printf("Right brace detected.\n");
                while (stk.top().s != "(")
                {
                    q.push(stk.top());
                    //cout << "Push " << stk.top().s << " into queue from stack.\n";
                    stk.pop();
                }
                stk.pop();
                continue;
            }
            else
            {
                while (!stk.empty() && priority(i) <= priority(stk.top().s))
                {
                    //printf("Higher priority detected.\n");
                    q.push(stk.top());
                    //cout << "Push " << stk.top().s << " into queue from stack.\n";
                    stk.pop();
                }
                //cout << "Push " << i << " into stack.\n";
                stk.push(aUtO(i));
                continue;
            }
        }
        else if (is_func(i))
        {
            //printf("Function detected.\n");
            while (!stk.empty() && priority(i) <= priority(stk.top().s))
            {
                q.push(stk.top());
                //cout << "Push " << stk.top().s << " into queue from stack.\n";
                stk.pop();
            }
            //cout << "Push " << i << " into stack.\n";
            stk.push(aUtO(i));
        }
        else if (classifier(i) != NaN)
        {
            //this is a num
            //printf("Number detected.\n");
            q.push(aUtO(BigNum(i)));
            //cout << "Push " << i << " into queue.\n";
        }
        else if (contains(i))
        {
            //this is a variable
            //printf("Variable detected.\n");
            q.push(aUtO(value_of(i)));
            //cout << "Push " << toString(value_of(i), -1) << " into queue.\n";
        }
        else
        {
            //wrong input
            //cout << "Wrong input format! Type -h for help." << endl;
            BigNum err = BigNum();
            err.type = NaN;
            return err;
        }
    }
    while (!stk.empty())
    {
        q.push(stk.top());
        //cout << "Push " << stk.top().s << " into queue from stack.\n";
        stk.pop();
    }
    BigNum x, y;
    aUtO cur, tmp;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        if (cur.is_num)
        {
            stk.push(cur);
        }
        else
        {
            x = stk.top().v;
            stk.pop();
            if (is_operator(cur.s[0]))
            {
                y = stk.top().v;
                stk.pop();
                stk.push(calc(y, x, cur.s[0]));
            }
            else if (is_func(cur.s))
            {
                if(cur.s=="exp")
                {
                    stk.push(aUtO(to_BigNum(exp(to_double(x)))));
                }
                else if(cur.s=="ln")
                {
                    stk.push(aUtO(to_BigNum(log(to_double(x)))));
                }
                else if(cur.s=="cos")
                {
                    stk.push(aUtO(to_BigNum(cos(to_double(x)))));
                }
                else if(cur.s=="sin")
                {
                    stk.push(aUtO(to_BigNum(sin(to_double(x)))));
                }
                else if(cur.s=="sqrt")
                {
                    stk.push(aUtO(to_BigNum(sqrt(to_double(x)))));
                }
            }
        }
    }
    return stk.top().v;
}