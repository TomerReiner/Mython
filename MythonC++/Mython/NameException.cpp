#include "NameException.h"

NameException::NameException(string varName) : exception()
{
    this->errorMessage = "NameError: name \'" + varName + "\' is not defined";
}

const char* NameException::what() const throw()
{

    return this->errorMessage.c_str();
}
