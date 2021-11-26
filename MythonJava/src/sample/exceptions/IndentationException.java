package sample.exceptions;

import java.awt.*;

public class IndentationException extends InterpreterException {
    @Override
    public void printStackTrace() {
        System.out.println(ANSI_RED + "IndentationError: unexpected indent" + ANSI_RESET);
    }
}
