package sample.exceptions;

public class SyntaxException extends InterpreterException {

    @Override
    public void printStackTrace() {
        System.out.println(ANSI_RED + "Syntax Error" + ANSI_RESET);
    }
}
