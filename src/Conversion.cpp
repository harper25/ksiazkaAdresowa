#include "Conversion.h"

Conversion::Conversion()
{
    //ctor
}

int Conversion::string2int(std::string number)
{
    return atoi(number.c_str());
}
