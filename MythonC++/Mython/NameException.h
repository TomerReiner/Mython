#pragma once

#include <iostream>
#include <string>
#include <format>

using namespace std;

class NameException : public exception
{
private:
	string errorMessage;

public:
	NameException(string varName);
	const char* what() const throw();
};

