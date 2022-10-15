#ifndef PROJECT02_VARIA_H
#define PROJECT02_VARIA_H

#include "big_num.h"
#include <bits/stdc++.h>

using namespace std;

void trim(string &s);

BigNum value_of(string name);

void insert(string name, string val);

void insert(string name, BigNum val);

bool remove(string name);

bool modify(string name, BigNum val);

bool contains(string name);

int add(string s);

void value_list(int precision);



#endif //PROJECT02_VARIA_H
