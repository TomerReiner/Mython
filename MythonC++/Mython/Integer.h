#pragma once

#include <iostream>
#include "Type.h"

using namespace std;

class Integer : public Type
{
private:
	int value;
public:
	Integer(int value);
	Integer(int value, bool isTemp);
	const bool IsPrintable();
	string ToString();
	int GetValue();
	void SetValue(int value);
	Integer* Clone();
	string GetType();
};

