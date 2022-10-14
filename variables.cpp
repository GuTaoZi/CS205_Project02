#include "bits/stdc++.h"
#include "big_num.h"
#include "functions.h"
using namespace std;

const regex duplicate_eq(".*=.*=.*");
const regex assignment(".*=.*");
map<string, BigNum> var_list;

BigNum value_of(string name)
{
    return var_list.find(name)->second;
}

void insert(string name,string val)
{
    var_list.insert(pair<string,BigNum>(name,BigNum(val)));
}

void insert(string name,BigNum val)
{
    var_list.insert(pair<string,BigNum>(name,val));
}

bool contains(string name)
{
    return var_list.count(name);
}

bool remove(string name)
{
    if(contains(name))
    {
        var_list.erase(name);
        return true;
    }
    return false;
}

bool modify(string name,BigNum val)
{
    bool flag=remove(name);
    if(flag)
    {
        insert(name,val);
        return true;
    }
    return false;
}