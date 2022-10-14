#include "bits/stdc++.h"
#include "big_num.h"
#include "varia.h"

using namespace std;

const regex duplicate_eq(".*=.*=.*");
const regex assignment("^\\D+\\w*=.+");
const regex is_eq(".*=.*");
map<string, BigNum> var_list;

BigNum value_of(string name)
{
    return var_list.find(name)->second;
}

void insert(string name, string val)
{
    var_list.insert(pair<string, BigNum>(name, BigNum(val)));
}

void insert(string name, BigNum val)
{
    var_list.insert(pair<string, BigNum>(name, val));
}

bool contains(string name)
{
    return var_list.count(name);
}

bool remove(string name)
{
    if (contains(name))
    {
        var_list.erase(name);
        return true;
    }
    return false;
}

bool modify(string name, BigNum val)
{
    bool flag = remove(name);
    if (flag)
    {
        insert(name, val);
        return true;
    }
    return false;
}

int add(string s)
{
    if (regex_match(s, duplicate_eq) || !regex_match(s, assignment))
    {
        if(!regex_match(s,is_eq))
        {
            return 0;
        }
        return -1;
    }
    bool flg = false;
    string lhs = "";
    string rhs = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (flg)
        {
            rhs += string(1, s[i]);
        }
        else
        {
            if (s[i] == '=')
            {
                flg = true;
                continue;
            }
            lhs += string(1, s[i]);
        }
    }
    if (classifier(rhs) == NaN)
    {
        return -2;
    }
    if (contains(lhs))
    {
        modify(lhs, BigNum(rhs));
    }
    else
    {
        insert(lhs, rhs);
    }
    cout<<"Assign "<<rhs<<" to "<<lhs<<endl;
    return 1;
}