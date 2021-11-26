#include "Type.h"

Type::Type()
{
	_isTemp = false;
}

Type::Type(bool isTemp)
{
	_isTemp = isTemp;
}

bool Type::IsTemp()
{
	return _isTemp;
}

void Type::SetTemp(bool isTemp)
{
	_isTemp = isTemp;
}
