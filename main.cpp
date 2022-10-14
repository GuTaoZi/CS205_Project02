#include <iostream>
#include "big_num.h"
#include "functions.h"

using namespace std;

int main()
{
//    string s1,s2;
//    char op;
//    cin>>s1>>op>>s2;
//    BigNum a=BigNum(s1);
//    BigNum b=BigNum(s2);
//    cout<<toString(calc(a, b, op), -1);
    string s;
    getline(cin, s);
    cout << toString(calculate(s), -1);
}
