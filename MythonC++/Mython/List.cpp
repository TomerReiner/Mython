#include "List.h"

List::List(vector<Type*> values, string originalList) : Sequence(false)
{
	this->values = values;
}

List::List(bool isTemp, vector<Type*> values, string originalList) : Sequence(isTemp)
{
	this->values = values;
}

const bool List::IsPrintable()
{
	return true;
}

/// <summary>
/// This function appends a value to the list.
/// </summary>
/// <param name="value"></param>
void List::Append(Type * t)
{
	this->values.push_back(t);
}

List* List::Clone()
{
	return new List(this->_isTemp, this->values, this->originalList);
}

string List::GetOriginalList()
{
	return this->originalList;
}

string List::GetType()
{
	return TYPE_LIST;
}

int List::Len()
{
	return this->values.size();
}

string List::ToString()
{
	if (this->values.empty())
		return "[]";

	string s = "[";

	for (int i = 0; i < this->values.size() - 1; i++)
	{
		s += this->values[i]->ToString();
		s += ", ";
	}
	s += this->values[this->values.size() - 1]->ToString();
	s += "]";
	return s;
}
