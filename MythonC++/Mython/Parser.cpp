#include <iostream>
#include <string>
#include "math.h"
#include "Parser.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "Type.h"
#include "Boolean.h"
#include "Integer.h"
#include "String.h"
#include "Void.h"

using namespace std;

/// <summary>
/// This function counts how many times c appears in s.
/// </summary>
/// <param name="s"></param>
/// <param name="c"></param>
/// <returns></returns>
int Parser::Count(string s, char c)
{
    int count = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
            count++;
    }
    return count;
}

vector<string> Parser::ParseListString(string value)
{
    int index = 0;
    vector<string> items = vector<string>();
    for (int i = 0; i < value.length(); i++)
    {
        string s = "";
        while (i < value.length() && value[i] != ',')
        {
            s += value[i];
            i++;
        }
            items.push_back(RemoveSpaces(s));
    }
    return items;
}

/// <summary>
/// This function splits a string based on character delimiter.
/// </summary>
/// <param name="command">A command to split</param>
/// <param name="delimiter">A char delimiter.</param>
/// <returns>Split array.</returns>
/// <example>
///     >>> SplitStrings("x = 78", ' ')
///     >>> {"x", "=", "78"}
/// </example>
void Parser::SplitString(string split[], string command, char delimiter)
{
    string value = "";
    int index = 0;

    if (command.find_first_of('=') != command.find_last_of('='))
        return;

    while (index < command.length() && command[index] != delimiter) // Get the first slice.
    {
        value += command[index];
        index++;
    }
    while (index < command.length() && command[index] == delimiter) { index++; } // Skip all the delimiter characters.

    split[0] = value;
    value = "";

    while (index < command.length() && command[index] != delimiter) // Get the second slice.
    {
        value += command[index];
        index++;
    }
    split[1] = value;
}

/// <summary>
/// This function removes all the spaces at the beginning and the end of a string.
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
string Parser::RemoveSpaces(string value)
{
    int beginIndex = 0;
    int stopIndex = value.length() - 1;

    while (beginIndex < value.length() && value[beginIndex] == ' ')
        beginIndex++;
    while (stopIndex >= 0 && value[stopIndex] == ' ')
        stopIndex--;

    return value.substr(beginIndex, stopIndex + 1);
}

bool Parser::IsList(string value)
{
    return value[0] == '[' && value[value.length() - 1] == ']';
}

/// <summary>
/// This function parses a list.
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
Type* Parser::ParseList(string value)
{
    List* lst;

    if (value == "[]")
        return new List(true, vector<Type*>());

    value = value.substr(1, value.length() - 2);
        
    vector<string> items = ParseListString(value);
    vector<Type*> list;

    for (int i = 0; i < items.size(); i++)
    {
        try
        {
            Type* t = GetType(items[i]);
            list.push_back(t);
        }
        catch (InterperterException& e)
        {
            throw e;
        }
    }
    lst = new List(true, list);
    return lst;
}

/// <summary>
/// This function checks if a command is a variable declaration.
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
bool Parser::MakeAssignment(string command)
{
    int commandLength = command.length();

    int indexEqual = command.find('=');
    int indexQuotationMarks = command.find('\"');
    int indexApostrophe = command.find('\'');

    string split[] = { "", "" };

    if (indexEqual < 0)
        return false;

    if (indexEqual > 0) // Check if a command is a vairable copy command.
    {
        SplitString(split, command, '=');

        string varName = RemoveSpaces(split[VAR_NAME_INDEX]);
        string value = RemoveSpaces(split[VALUE_INDEX]);

        if (varName == "" && value == "")
            throw SyntaxException();

        if (Parser::CanAdd(varName, value)) // If it's an addition statement.
        {
            try
            {
                Add(varName, value);
                return true;
            }
            catch (InterperterException& e)
            {
                throw e;
            }
        }

        if (!IsLegalVarName(varName))
            throw NameException(varName);

        if (IsVariableName(value))
        {
            if (dynamic_cast<List*>(variables[varName]) != NULL) // If the value is not a list we want to create a clone of the variable.
                variables[varName] = variables[value]->Clone();
            else // If the variable is a list we want a direct pointer to the original list.
                variables[varName] = variables[value];

            return true;
        }
        else
        {
            try
            {
                Type* t = GetType(value);
                t->SetTemp(false);
                variables[varName] = t;
                return true;
            }
            catch (SyntaxException& e)
            {
                throw e;
            }
        }
    }
    return false;
}

/// <summary>
/// This function parses a command in Python.
/// </summary>
/// <param name="command">A command in Python.</param>
/// <returns>The output of the command.</returns>
Type* Parser::ParseString(string command)
{
    Type* t;

    if (command.length() == 0)
        return NULL;

    if (command[0] == ' ' || command[0] == '\t') // If the line begins wil an illegal indentation.
        throw IndentationException();

    command = RemoveSpaces(command);

    if (IsDeleteStatement(command)) // If the command is a delete command.
    {
        try
        {
            Delete(command);
            return NULL;
        }
        catch (InterperterException &e)
        {
            throw e;
        }
    }

    if (IsTypeStatement(command)) // If the command is "type(value)".
    {
        PrintType(command);
        return NULL;
    }

    if (IsLenStatement(command))
    {
        try
        {
            Len(command);
            return NULL;
        }
        catch (InterperterException& e)
        {
            cout << e.what() << endl;
            return NULL;
        } 
    }

    bool isAssignment =  MakeAssignment(command);
    bool isValuePrint = IsValuePrint(command);

    if (isValuePrint)
    {
        Type* t = GetType(command);
        cout << t->ToString() << endl;
        return NULL;
    }

    if (isAssignment) // If the given command is an assignment
    {
        t = new Void(true);
        return t;
    }
    else // If it's a print variable statemnt.
    {
        Type* t = GetVariableValue(command);

        if (t == nullptr)
            throw NameException(command);
        else
            cout << t->ToString() << endl;
    }
    return NULL;
}

/// <summary>
/// This function returns the type of a value.
/// </summary>
/// <param name="value">A value. Can be int, string or boolean</param>
/// <returns>The class that represents this value.</returns>
Type* Parser::GetType(string value)
{
    Type* type;

    if (value.length() == 0) // If the value is empty we will return a null value.
        throw SyntaxException();

    // Check if the values are boolean values.
    if (value == "True")
    {
        type = new Boolean(true, true);
        return type;
    }
    else if (value == "False")
    {
        type = new Boolean(false, true);
        return type;
    }
    // From here the value can be a string or an int.

    int numericValue;

    try // Try to cast the value to an integer.
    {
        numericValue = stoi(value);
    }
    catch (exception& e) // If the cast fails then the value must be a string or a list.
    { 
        if (IsList(value)) // If the value is a list.
        {
            try { // Parse the list.
                type = ParseList(value);
                return type;
            }
            catch (InterperterException& e) // There is an error with the list.
            {
                throw e;
            }
        }

        if (!String::IsValidString(value))
            throw SyntaxException();

        type = new String(value, true);
        return type;
    }
    type = new Integer(numericValue, true);
    return type;
}

/// <summary>
/// This function checks if a variable name is valid.
/// A valid variable name can only include english letters, digits and an underscore.
/// The first character must be an underscore or an english letter. A valid variable name cannot include digits only.
/// In addition, a valid variable name cannot be a python keyword.
/// </summary>
/// <param name="varName">The name of the variable</param>
/// <returns>true if varName is valid, false otherwise.</returns>
bool Parser::IsLegalVarName(string varName)
{
    for (string s : pythonKeywords)
    {
        if (varName == s) // If varName is a python keyword then it's not a valid variable name.
            return false;
    }

    int countDigit = 0;

    for (char c : varName)
    {
        if (!((c >= '0' && c <= '9') || (c == '_') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) // If one of the letters in varName is not valid.
            return false;
        if (c >= '0' && c <= '9')
            countDigit++;
    }
    return countDigit != varName.length() && !(varName[0] >= '0' && varName[0] <= '9'); // Check if the first character is an underscore or a letter, and if not all the characters in varName are digits.
}

Type* Parser::GetVariableValue(string varName)
{
    return variables[varName];
}
/// <summary>
/// This function clears variables.
/// </summary>
void Parser::RemoveVariables()
{
    for (pair<string, Type*> p : variables)
        delete p.second;
}

/// <summary>
/// This function checks whether a string is a variable name.
/// </summary>
/// <param name="varName"></param>
/// <returns></returns>
bool Parser::IsVariableName(string varName)
{
    for (pair<string, Type*> p : variables)
    {
        if (p.first == varName)
            return true;
    }
    return false;
}

/// <summary>
/// This function checks is a declatation is an addition statement.
/// </summary>
/// <param name="varName"></param>
/// <param name="value"></param>
/// <returns></returns>
bool Parser::CanAdd(string varName, string value)
{
    if (varName[varName.length() - 1] != '+')
        return false;
    return IsVariableName(value) || GetType(value) != NULL;
}

/// <summary>
/// This function adds a value to a list or to an integer or a string.
/// </summary>
/// <param name="varName"></param>
/// <param name="value"></param>
/// <returns></returns>
void Parser::Add(string varName, string value)
{
    varName = RemoveSpaces(varName.substr(0, varName.length() - 1));
    if (!IsVariableName(varName)) // If the isn't such variable name.
        throw NameException(varName);
    Type* t;

    if (!IsVariableName(value)) // If its an addition of a value.
    {
        try
        {
            t = GetType(value);
        }
        catch (InterperterException &e)
        {
            throw e;
        }
    }
    else // If its an addition of an existing values.
    {
        t = variables[value];
    }

    String* varNameStringValue = dynamic_cast<String*>(variables[varName]);
    Integer* varNameIntegerValue = dynamic_cast<Integer*>(variables[varName]);
    List* varNameListValue = dynamic_cast<List*>(variables[varName]);

    String* valueString = dynamic_cast<String*>(t);
    Integer* valueInteger = dynamic_cast<Integer*>(t);

    if (varNameStringValue != NULL && valueString != NULL) // If the value is a string
    {
        string varNameStr = varNameStringValue->GetValue();
        varNameStringValue->SetValue(varNameStr.substr(0, varNameStr.length() - 1) + valueString->GetValue().substr(1));
        variables[varName] = varNameStringValue;
        return;
    }
    else if (varNameIntegerValue != NULL && valueInteger != NULL) // If the value is an integer.
    {
        varNameIntegerValue->SetValue(varNameIntegerValue->GetValue() + valueInteger->GetValue());
        variables[varName] = varNameIntegerValue;
        return;
    }
    else if (varNameListValue != NULL) // If we wna tot append an item to the list.
    {
        varNameListValue->Append(t);
        return;
    }
// TODO - add list.
    throw SyntaxException();
}

/// <summary>
/// This function checks if the given command is a print value statement.
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
bool Parser::IsValuePrint(string command)
{
    try
    {
        Type* t = GetType(command);
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

/// <summary>
/// This function checks if a command is a command from this form: type(value).
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
bool Parser::IsTypeStatement(string command)
{
    if (command.length() < 6)
        return false;
    string type = command.substr(0, 5);
    return type == "type(" && command[command.length() - 1] == ')'; // Check if the command begin with "type(" and ends with a ")".
}

/// <summary>
/// This function prints the type of a value.
/// </summary>
/// <param name="command"></param>
void Parser::PrintType(string command)
{
    if (command == "type()")
        return;

    string value = command.substr(5, command.length() - 1);
    value = value.substr(0, value.length() - 1);
    value = RemoveSpaces(value);


    if (IsVariableName(value)) // If the user wants to check the type of a variable.
    {

        cout << variables[value]->GetType() << endl;
    }

    else
    {
        try
        {
            Type* t = GetType(value);
            cout << t->GetType() << endl;
        }
        catch (InterperterException &e)
        {
            cout << e.what() << endl;
        }
    }
}
/// <summary>
/// This function checks if a statement is a delete statement.
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
bool Parser::IsDeleteStatement(string command)
{
    if (command.length() < 5) // the command must be at least five characters long("del varName").
        return false;

    string del = command.substr(0, 3);
    return del == "del" && command[3] == ' '; // After the keyword a space must be present.
}

void Parser::Delete(string command)
{
    string varName = command.substr(4);
    varName = RemoveSpaces(varName);

    if (!IsVariableName(varName))
        throw NameException(varName);
    
    variables.erase(varName);
}

/// <summary>
/// This function checks if a statement is a length statement.
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
bool Parser::IsLenStatement(string command)
{
    if (command.length() < 4)
        return false;
    return command.substr(0, 4) == "len(";
}

/// <summary>
/// This function finds the length of a given variables.
/// If the variable is not a string or a list, the function will throw an exception.
/// </summary>
/// <param name="command"></param>
void Parser::Len(string command)
{
    string value = command.substr(4);
    value = value.substr(0, value.length() - 1);
    value = RemoveSpaces(value);
    Type* t;

    if (IsVariableName(value)) // If the argument is an existing variable.
        t = variables[value];

    else // If the argument is a value.
    {
        try
        {
            t = GetType(value);
        }
        catch (InterperterException &e)
        {
            cout << e.what();
            return;
        }
    }
    
    if (t->GetType() == TYPE_LIST) // If the value is a list.
    {
        List* list = dynamic_cast<List*>(t);
        cout << list->Len() << endl;
    }

    else if (t->GetType() == TYPE_STR) // If the value is a string.
    {
        String* str = dynamic_cast<String*>(t);
        cout << str->Len() << endl;
    }
    else // The value isn't string nor a list, so the function will throw an exception.
        throw SyntaxException();
}
