#include "Boolean.h"

Boolean::Boolean(bool value) : Type(false)
{
	this->value = value;
}

Boolean::Boolean(bool value, bool isTemp) : Type(isTemp)
{
	this->value = value;
}

const bool Boolean::IsPrintable()
{
	return true;
}

string Boolean::ToString()
{
	return to_string(this->value);
}

Boolean* Boolean::Clone()
{
	return new Boolean(this->value, this->_isTemp);
}

string Boolean::GetType()
{
	return "<type \'bool\'>";
}
