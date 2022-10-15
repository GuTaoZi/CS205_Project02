#include "bits/stdc++.h"
#include "big_num.h"
#include "functions.h"
#include "varia.h"

using namespace std;

int precision=-1;

void init()
{
    insert("PI","3.1415926535897932384626433832795");
    insert("_e","2.718281828459045235360287");
}

void print_help()
{
    printf(" Command set:\n"
           " #h help\n"
           " #p [num] set precision(-1 for as accurate as possible)\n"
           " #n number format\n"
           " #f function list\n"
           " #v variable list\n"
           " [variable_name]=[num] set/modify variable\n"
           " #q quit\n");
}

void set_precision(string s)
{
    if(s[2]==' ')
    {
        s.erase(0,3);
        if(s.length()==2&&s[0]=='-'&&s[1]=='1')
        {
            precision=-1;
        }
        else
        {
            int p=0;
            for(int i=s.length()-1;i>=0;i--)
            {
                if(!isdigit(s[i]))
                {
                    p= -1;
                    break;
                }
                p*=10;
                p+=s[i]-'0';
            }
            if(p<=0)
            {
                printf("Pls input a right number for precision!\n");
            }
            else
            {
                precision=p;
                printf("Set precision to %d\n",precision);
            }
        }
    }
    else
    {
        printf("Wrong input format detected, pls input again. Type #h for help.\n");
    }
}

void print_type()
{
    printf("Type list: \n"
           " PURE_INT : -19260817\n"
           " INT_WITH_E : -1926e-0817\n"
           " INT_WITH_SUFFIX : -19260817k/m/g/t\n"
           " PURE_FLOAT : -1926.0817\n"
           " FLOAT_WITH_E : -1926.08e-17\n"
           " FLOAT_WITH_SUFFIX : -1926.0817k/m/g/t\n"
           " ABBR_FLOAT : -.19260817\n");
}

void print_func()
{
    printf("Function list:\n"
           "sqrt(x)\t Rooting"
           "exp(x)\tnatural exponential\n"
           "ln(x)\tNatural logarithm\n"
           "sin(x) sine\n"
           "cos(x) cosine\n");
}

int main()
{
    string s="";
    init();
    while(s!="#q")
    {
        printf(">>>");
        getline(cin, s);
        if(s=="#q")
        {
            return printf("Good bye~ :)\n")&0;
        }
        else if(s=="#h")
        {
            print_help();
            continue;
        }
        else if(s[0]=='#'&&s[1]=='p')
        {
            set_precision(s);
        }
        else if(s=="#n")
        {
            print_type();
            continue;
        }
        else if(s=="#f")
        {
            print_func();
            continue;
        }
        else if(s=="#v")
        {
            value_list(precision);
            continue;
        }
        else
        {
            trim(s);
            int flag=add(s);
            if(flag==0)
            {
                cout << to_string(calculate(s), precision) << endl;
                continue;
            }
            else if(flag==-1)
            {
                printf("Wrong format of equation detected, pls try again. Type #h for help.\n");
            }
            else if(flag==-2)
            {
                printf("Wrong format of value detected, pls try again. Type #h for help.\n");
            }
        }
    }
}
