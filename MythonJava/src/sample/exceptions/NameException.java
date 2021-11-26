package sample.exceptions;

public class NameException extends InterpreterException {

    private String errorMessage;

    public NameException(String name) {
        this.errorMessage = "Name error: name \'" + name + "\' is not defined";
    }

    @Override
    public void printStackTrace() {
        System.out.println(ANSI_RED + this.errorMessage + ANSI_RESET);
    }
}
