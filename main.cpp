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
    printf((a<b)?"a<b":"a>=b");
    return 0;
}
