#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "Type.h"
#include "List.h"
#include "NameException.h"

#define VAR_NAME_INDEX 0
#define VALUE_INDEX 1

using namespace std;

const static string pythonKeywords[] = { "and", "as", "assert", "break", "class", "continue", "def", "del",
						"elif", "else", "except", "False", "finally", "for", "from", "global", "if", "import",
						"in", "is", "lambda", "None", "nonlocal", "not", "or",
						"pass", "raise", "return", "True", "try", "while", "with", "yield" };

static unordered_map<string, Type*> variables = unordered_map<string, Type*>();

class Parser
{
private:
	static int Count(string s, char c);
	static vector<string> ParseListString(string value);
	static void SplitString(string split[], string command, char delimiter);
	static string RemoveSpaces(string value);
	static bool IsList(string value);
	static Type* ParseList(string value);

public:
	static bool MakeAssignment(string command);
	Type* ParseString(string command);
	static Type* GetType(string value);
	static bool IsLegalVarName(string varName);
	static Type* GetVariableValue(string varName);
	static void RemoveVariables();
	static bool IsVariableName(string varName);
	static bool CanAdd(string varName, string value);
	static void Add(string varName, string value);
	static bool IsValuePrint(string command);
	static bool IsTypeStatement(string command);
	static void PrintType(string command);
	static bool IsDeleteStatement(string command);
	static void Delete(string command);
	static bool IsLenStatement(string command);
	static void Len(string command);
};

