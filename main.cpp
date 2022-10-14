#include "bits/stdc++.h"
#include "big_num.h"
#include "functions.h"
#include "varia.h"

using namespace std;

int main()
{
    string s="";
    while(s!="#quit")
    {
        printf(">>>");
        getline(cin, s);
        trim(s);
        if(s=="#quit")
        {
            return 0;
        }
        else if(s=="#help")
        {

        }
        else
        {
            int flag=add(s);
            if(flag==0)
            {
                cout << toString(calculate(s), -1)<<endl;
                continue;
            }
            else if(flag==-1)
            {
                printf("Wrong format of equation detected, pls try again. Type #help for help.\n");
            }
            else if(flag==-2)
            {
                printf("Wrong format of value detected, pls try again. Type #help for help.\n");
            }
        }
    }
}
