#include "InterperterException.h"

const char* InterperterException::what() const throw () 
{
	return "Interpreter Error";
}
