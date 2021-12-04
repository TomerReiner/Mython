#include "String.h"

String::String(string value) : Sequence()
{
	this->value = value;
}

String::String(string value, bool isTemp) : Sequence(isTemp)
{
	this->value = value;
}

const bool String::IsPrintable()
{
	return true;
}

string String::ToString()
{
	return this->FormatString();
}

/// <summary>
/// This function checks if a string is a valid string.
/// </summary>
/// <param name="value">A string</param>
/// <returns>true if the string is valid, false otherwise.</returns>
const bool String::IsValidString(const string value)
{
	if (value.length() == 0) // Empty string is a valid string.
		return true;
	
	int beginIndex = 0;
	int endIndex = value.length();

	if (value[0] != '\'' && value[0] != '\"')
		return false;

	char first = value[0];

	if (first != value[value.length() - 1])
		return false;

	for (int i = 1; i < value.length() - 1; i++)
	{
		if (value[i] == first) // If the string is not properly formatted.
			return false;
	}

	return true;
}

/// <summary>
/// This function formats a string for String::ToString().
/// This function assumes that the string is valid.
/// </summary>
/// <param name="value">A string to format</param>
/// <returns>A formatted string.</returns>
const string String::FormatString()
{
	return '\'' + this->value.substr(1, this->value.length() - 2) + '\'';
}

string String::GetValue()
{
	return this->value;
}

void String::SetValue(string value)
{
	this->value = value;
}

String* String::Clone()
{
	return new String(this->value, this->_isTemp);
}

string String::GetType()
{
	return TYPE_STR;
}

int String::Len()
{
	return this->value.length() - 2;
}
