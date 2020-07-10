#include <iostream>
#include "class.h"
using namespace std;

int main()
{
    Word one;
    one.operate();
    Addtoken("@");
    Syntax two;
    two.parse();
    Meaning three;
    three.parse();
}
