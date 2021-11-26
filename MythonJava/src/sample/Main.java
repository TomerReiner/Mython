package sample;


import sample.exceptions.InterpreterException;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        Parser parser = new Parser();

        while (true) {
            System.out.print(">>> ");
            String command = in.nextLine();

            if (command.equals("end()")) // If the user wants to end the interpreter.
                break;

            try {
                parser.parseString(command);
            }
            catch (InterpreterException e) {
                e.printStackTrace();
            }
        }
    }
}
