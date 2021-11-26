package sample;

import sample.exceptions.IndentationException;
import sample.exceptions.InterpreterException;
import sample.exceptions.NameException;
import sample.exceptions.SyntaxException;
import sample.types.*;
import sample.types.Void;

import java.util.ArrayList;
import java.util.HashMap;

public class Parser {

    public static final int VARIABLE_NAME_INDEX = 0;
    public static final int VALUE_INDEX = 1;

    public static HashMap<String, Type> variables = new HashMap<>();

    public static final String[] PYTHON_KEYWORDS = { "and", "as", "assert", "break", "class", "continue", "def", "del",
            "elif", "else", "except", "False", "finally", "for", "from", "global", "if", "import",
            "in", "is", "lambda", "None", "nonlocal", "not", "or",
            "pass", "raise", "return", "True", "try", "while", "with", "yield" };

    /**
     * This function checks if a string is valid.
     * @param s
     * @return <code>true</code> if the string is valid, <code>false</code> otherwise.
     */
    private boolean isValidStringValue(String s) {
        if (s.charAt(0) != '\"' && s.charAt(s.length() - 1) != '\'') // If the string does not begin with quotation mark or apostrophe.
            return false;

        if (s.charAt(0) == '\"') {
            for (int i = 1; i < s.length() - 1; i++) {
                if (s.charAt(i) == '\"')
                    return false;
            }
            return s.charAt(s.length() - 1) == '\"';
        }
        for (int i = 1; i < s.length() - 1; i++) {
            if (s.charAt(i) == '\'')
                return false;
        }
        return s.charAt(s.length() - 1) == '\'';
    }

    /**
     * This function checks if a string is a list.
     * @param value
     * @return <code>true</code> if <code>value</code> is a list, false otherwise.
     */
    private boolean isList(String value) {
        return value.charAt(0) == '[' && value.charAt(value.length() - 1) == ']';
    }

    private List parseList(String value) throws InterpreterException {
        value = value.substring(1, value.length() - 1);

        if (value.length() == 0)
            return new List(new ArrayList<>());

        String[] values = value.split(",");

        for (int i = 0; i < values.length; i++)
            values[i] = values[i].strip();

        ArrayList<Type> types = new ArrayList<>();

        for (int i = 0; i < values.length; i++) {
            try {
                if (variables.containsKey(values[i])) // If the item is a variable.
                    types.add(variables.get(values[i]));
                else { // If the item is a value.
                    Type t = getType(values[i]);
                    types.add(t);
                }
            }
            catch (InterpreterException e) {
                throw e;
            }
        }
        return new List(true, types);
    }

    /**
     * This function checks the type of a value.
     * @param value A value.
     * @return An object that represents the value.
     */
    public Type getType(String value) throws InterpreterException {
        if (value == null || value.length() == 0)
            return null;

        value = value.strip();

        if (value.equals("True"))
            return new Bool(true, true);
        if (value.equals("False"))
            return new Bool(true, false);
        // If value is a boolean.

        try { // If value is an integer.
            int i = Integer.parseInt(value);
            return new Int(true, i);
        }
        catch (Exception e) { // From this point value can be a list or a string.
            if (value.equals("None")) // If the value is a null value.
                return new Str(true, null);
            if (isList(value)) { // If the value is a list.
                try {
                    return parseList(value);
                }
                catch (InterpreterException e1) { // If one of the values is not properly
                    throw e1;
                }
            }

            if (!isValidStringValue(value))
                throw new NameException(value);
            return new Str(true, value);
        }
    }

    /**
     * This function checks if a variable name is valid.
     * A valid variable name can only include digits, an underscore and english letters.
     * A valid variable name cannot start with a digit and cannot include only digits.
     * @param varName The variable name.
     * @return <code>true</code> if <code>varName</code> is valid, <code>false</code> otherwise.
     */
    public static boolean isLegalVariableName(String varName) {
        if (varName == null || varName.length() == 0)
            return false;

        if (varName.charAt(0) >= '0' && varName.charAt(0) <= '9')
            return false;

        for (String keyword : PYTHON_KEYWORDS) { // Check whether varName is a keyword.
            if (varName.equals(keyword))
                return false;
        }

        for (int i = 0; i < varName.length(); i++) {
            if (!((varName.charAt(i) >= '0' && varName.charAt(i) <= '9') ||
                    (varName.charAt(i) >= 'a' && varName.charAt(i) <= 'z') ||
                    (varName.charAt(i) >= 'A' && varName.charAt(i) <= 'Z') ||
                    varName.charAt(i) == '_'
            ))
                return false;
        }
        return true;
    }

    /**
     * This function checks if a string is a variable declaration.
     * This function assigns a value to a variable.
     * @param command A python command.
     * @return <code>true</code> if <code>command</code> is a variable declaration, false otherwise.
     */
    private boolean isAssignment(String command) throws InterpreterException {
        int firstEqualIndex = command.indexOf('=');
        int indexQuotationMarks = command.indexOf('\"');
        int indexApostrophe = command.indexOf('\'');

        if (firstEqualIndex == 0)
            throw new SyntaxException();
        if (firstEqualIndex < 0)
            return false;

        if ((firstEqualIndex < indexApostrophe || firstEqualIndex < indexQuotationMarks) || (indexApostrophe < 0 && indexQuotationMarks < 0)) { // If its a declaration on a new variable.
            String[] splitCommand = command.split("=");
            String varName = splitCommand[VARIABLE_NAME_INDEX].strip();
            String value = splitCommand[VALUE_INDEX].strip();

            try {
                if (canAdd(varName, value)) {
                    varName = varName.substring(0, varName.length() - 1).strip();
                    add(varName, value);
                    return true;
                }
            }
            catch (InterpreterException e) {
                throw e;
            }

            if (!isLegalVariableName(varName)) // If the variable name is illegal.
                throw new SyntaxException();

            if (variables.containsKey(value)) { // If it's a variable copy declaration.
                if (!variables.containsKey(value))
                    throw new NameException(varName);
                variables.put(varName, variables.get(value));
                return true;
            }
            Type t = getType(value);
            if (t == null)
                throw new SyntaxException();

            t.setTemp(false);
            variables.put(varName, t); // Add the variable.
            return true;
        }
        return false;
    }

    private boolean canAdd(String varName, String value) throws InterpreterException {
        if (!(varName.length() > 1 && varName.charAt(varName.length() - 1) == '+'))
            return false;

        varName = varName.substring(0, varName.length() - 1).strip();

        if (!variables.containsKey(varName)) // If there is a name error.
            throw new NameException(varName);
        try {
            if (variables.containsKey(value))
                return isLegalVariableName(varName);
            Type t = getType(value);
            return true;
        }
        catch (InterpreterException e) {
            throw e;
        }
    }

    /**
     * This function adds a value to a variable.
     * Note: You can only add a value to Str, Int or List variables.
     * To Str variables you can only add Str values/variables.
     * To Int variables you can only add Int values/variables.
     * To List variables you can add any values.
     * @param varName The variable to add a value to.
     * @param value The value to add.
     */
    private void add(String varName, String value) throws InterpreterException {
        Type t = variables.get(varName);

        Type update;

        if (variables.containsKey(value))
            update = variables.get(value);
        else
            update = getType(value);

        if (t instanceof List) { // If t is a list.
            ((List) t).append(getType(value));
            variables.put(varName, t);
        }

        if (t instanceof Int && update instanceof Int) {
            ((Int) t).setValue(((Int) t).getValue() + ((Int) update).getValue());
            variables.put(varName, t);
        }

        if (t instanceof Str && update instanceof Str) {
            String current = ((Str) t).getValue();
            String s = ((Str) update).getValue();
            ((Str) t).setValue(current.substring(0, current.length() - 1) + s.substring(1));
            variables.put(varName, t);
        }
    }

    /**
     * This function checks if a command is a variable print declaration.
     * @param command
     * @return
     */
    public boolean isVariablePrint(String command) throws InterpreterException {
        if (!variables.containsKey(command))
            throw new NameException(command);
        return variables.get(command).isPrintable();
    }

    /**
     * This function parses a python command.
     * @param command A python command.
     */
    public Type parseString(String command) throws InterpreterException {
        if (command.equals(""))
            return null;

        if (command.charAt(0) == ' ' || command.charAt(0) == '\t')
            throw new IndentationException();
        command = command.strip();

        try {
            boolean isAssignment = isAssignment(command);
            boolean isDeleteStatement = isDeleteStatement(command);
            boolean isTypeStatement = isTypeStatement(command);
            boolean isLenStatement = isLenStatement(command);

            if (isLenStatement) {
                len(command);
                return null;
            }

            if (isDeleteStatement) {
                delete(command);
                return null;
            }

            if (isTypeStatement) {
                printType(command);
                return null;
            }

            if (isAssignment)
                return new Void();
            else {
                boolean isVariablePrint = isVariablePrint(command);
                if (isVariablePrint)
                    System.out.println(variables.get(command).toString());
            }
        }
        catch (InterpreterException e) {
            throw e;
        }
        return null;
    }

    /**
     * This function checks if a command is a delete command.
     * @param command A python command.
     * @return <code>true</code> if the command is a delete command, <code>false</code> otherwise.
     */
    private boolean isDeleteStatement(String command) {
        return command.startsWith("del ");
    }

    /**
     * This function deletes a variable from <code>variables</code>.
     * @param command A python command.
     */
    private void delete(String command) {
        String value = command.substring(4).strip();

        if (variables.containsKey(value))
            variables.remove(value);
        else
            new NameException(value).printStackTrace();
    }

    /**
     * This function checks if a statement is a <code>type(value)</code> statement.
     * @param command A python command.
     * @return <code>true</code> if the command is a <code>type(value)</code>, false otherwise.
     */
    private boolean isTypeStatement(String command) {
        return command.startsWith("type(") && command.endsWith(")");
    }

    private void printType(String command) {
        String value = command.substring(5, command.length() - 1).strip(); // Get the value inside the function.

        if (value.equals("")) {
            new SyntaxException().printStackTrace();
            return;
        }

        if (variables.containsKey(value)) { // If the user wants to check the type of a variable.
            System.out.println(variables.get(value).getType());
            return;
        }
        try { // If the user wants to check the type of a value.
            Type t = getType(value);
            System.out.println(t.getType());
        }
        catch (InterpreterException e) {
            e.printStackTrace();
        }
    }

    private boolean isLenStatement(String command) {
        return command.startsWith("len(") && command.endsWith(")");
    }

    private void len(String command) throws InterpreterException{
        String value = command.substring(4, command.length() - 1).strip();

        if (value.equals(""))
            throw new SyntaxException();

        Type t;

        if (variables.containsKey(value)) // If the user wants to check the length of a variable.
            t = variables.get(value);
        else { // If the user wants to check the length of a value.
            try {
                t = getType(value);
            } catch (InterpreterException e) {
                e.printStackTrace();
                return;
            }
        }
        if (t instanceof Str)
            System.out.println(((Str)t).len());
        else if (t instanceof List)
            System.out.println(((List)t).len());
        else
            throw new SyntaxException();
    }
}
