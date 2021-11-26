#pragma once
#include "Type.h"
class Void : public Type
{
public:
	Void();
	Void(bool isTemp);
	const bool IsPrintable();
	string ToString();
	Void* Clone();
	string GetType();
};

