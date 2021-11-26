#pragma once

#include <iostream>
#include "Type.h"

using namespace std;

class Boolean : public Type
{
private:
	bool value;

public:
	Boolean(bool value);
	Boolean(bool value, bool isTemp);
	const bool IsPrintable();
	string ToString();
	Boolean* Clone();
	string GetType();
};

