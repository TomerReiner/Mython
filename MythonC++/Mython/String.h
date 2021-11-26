#pragma once

#include "Sequence.h"

class String : public Sequence
{
private:
	string value;

public:
	String(string value);
	String(string value, bool isTemp);
	const bool IsPrintable();
	string ToString();
	const static bool IsValidString(const string value);
	const string FormatString();
	string GetValue();
	void SetValue(string value);
	String* Clone();
	string GetType();

};

