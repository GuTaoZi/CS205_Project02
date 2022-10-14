#ifndef PROJECT02_FUNCTIONS_H
#define PROJECT02_FUNCTIONS_H

#include "big_num.h"
#include <bits/stdc++.h>

using namespace std;

BigNum value_of(string name);

void insert(string name,string val);

void insert(string name,BigNum val);

bool remove(string name);

bool modify(string name,BigNum val);

bool contains(string name);

#endif //PROJECT02_FUNCTIONS_H
