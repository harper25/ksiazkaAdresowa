#include "Conversion.h"
using namespace std;

Conversion::Conversion()
{
    //ctor
}

int Conversion::string2int(string number)
{
    return atoi(number.c_str());
}
