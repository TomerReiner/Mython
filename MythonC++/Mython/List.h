#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "Sequence.h"
#include "Parser.h"
#include "InterperterException.h"

using namespace std;

class List : public Sequence
{
private:
	string originalList;
	vector<Type*> values;

public:
	List(vector<Type*> values, string originalList="");
	List(bool isTemp, vector<Type*> values, string originalList="");
	const bool IsPrintable();
	void Append(Type * t);
	string ToString();
	List* Clone();
	string GetOriginalList();
	string GetType();
};

