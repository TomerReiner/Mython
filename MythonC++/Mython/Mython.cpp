#include <iostream>
#include <string>
#include <Windows.h>
#include "Parser.h"
#include "IndentationException.h"
#include "SyntaxException.h"

using namespace std;

const int NORMAL_OUTPUT_COLOR = 7;
const int ERROR_OUTPUT_COLOR = 4;
// TODO - check if can access from different files

void ChangeOutputColor(const int * color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), *color);
}

int main()
{
    string command;
    Parser parser = Parser();;
    cout << "Mython - My Python Interpreter version 1.0 by Tomer Gaming" << endl;

    while (true) {
        cout << ">>> ";
        getline(cin, command);

        if (command == "end()")
        {
            Parser::RemoveVariables();
            break;
        }
        else 
        {
            try 
            {
                parser.ParseString(command);
            }
            catch (exception & e)
            {
                ChangeOutputColor(&ERROR_OUTPUT_COLOR);
                cout << e.what() << endl;
                ChangeOutputColor(&NORMAL_OUTPUT_COLOR);
            }
        }
    }
}

