#include "Void.h"

Void::Void() : Type(false)
{
}

Void::Void(bool isTemp) : Type(isTemp)
{
}

const bool Void::IsPrintable()
{
    return false;
}

string Void::ToString()
{
    return string();
}

Void* Void::Clone()
{
    return new Void(this->_isTemp);
}

string Void::GetType()
{
    return "<type \'void\'>";
}
