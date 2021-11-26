#pragma once

#include <iostream>
#include <exception>

using namespace std;

class SyntaxException : public exception
{
public:
	const char* what() const throw ();

};

