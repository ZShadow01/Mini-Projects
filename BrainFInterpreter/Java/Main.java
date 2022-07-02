public class Main {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Missing argument: target file");
            System.exit(-1);
        }

        System.exit(new Interpreter(args[0]).run());
    }
}