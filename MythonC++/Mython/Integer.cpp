#include "Integer.h"

Integer::Integer(int value) : Type(false)
{
	this->value = value;
}

Integer::Integer(int value, bool isTemp) : Type(isTemp)
{
	this->value = value;
}

const bool Integer::IsPrintable()
{
	return true;
}


string Integer::ToString()
{
	return std::to_string(this->value);
}

int Integer::GetValue()
{
	return this->value;
}

void Integer::SetValue(int value)
{
	this->value = value;
}

Integer* Integer::Clone()
{
	return new Integer(this->value, this->_isTemp);
}

string Integer::GetType()
{
	return "<type \'int\'>";
}
