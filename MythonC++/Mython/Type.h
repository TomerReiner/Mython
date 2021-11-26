#pragma once

#include <iostream>
#include <string>

using namespace std;

class Type
{
protected:
	bool _isTemp;

public:
	Type();
	Type(bool isTemp);
	const virtual bool IsPrintable() = 0;
	bool IsTemp();
	void SetTemp(bool isTemp);
	virtual string ToString() = 0;
	virtual Type* Clone() = 0;
	virtual string GetType() = 0;
};

