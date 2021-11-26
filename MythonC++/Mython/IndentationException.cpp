#include "IndentationException.h"
#include <iostream>

const char* IndentationException::what() const throw () 
{
	return "IndentationError: unexpected indent";
}
