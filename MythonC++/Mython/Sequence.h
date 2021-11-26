#pragma once
#include "Type.h"

class Sequence : public Type
{
public:
	Sequence();
	Sequence(bool isTemp);
	const virtual bool IsPrintable() = 0;
	virtual string ToString() = 0;
	virtual Sequence* Clone() = 0;
	virtual string GetType() = 0;
};

