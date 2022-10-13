#include <iostream>
#include "big_num.h"

using namespace std;

struct BigNum a,b;

int main()
{
    string s1,s2;
    cin>>s1>>s2;
    a=BigNum(s1);
    b=BigNum(s2);
    a= standardize_exp(a);
    b= standardize_exp(b);
    print_BigNum(a,-1);
    cout<<endl;
    print_BigNum(b,-1);
    cout<<endl;
    print_BigNum(a/b,-1);
    cout<<endl;
    return 0;
}
