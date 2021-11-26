#pragma once

#include <iostream>
#include "InterperterException.h"

class IndentationException : public InterperterException
{
public:
	const char* what() const throw ();

};

