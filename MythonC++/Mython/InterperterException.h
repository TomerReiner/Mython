#pragma once
#include <iostream>
#include <exception>

using namespace std;

class InterperterException : public exception
{
public:
	const char * what () const throw ();

};

