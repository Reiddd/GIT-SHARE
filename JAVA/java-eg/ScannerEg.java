import java.util.Scanner;

public class ScannerEg {
    static void eg1() {
        System.out.println("example-1");

        String  text    = "1 fish 2 fish red fish blue fish";
        Scanner scanner = (new Scanner(text)).useDelimiter("\\s*fish\\s*");

        System.out.println(scanner.nextInt());
        System.out.println(scanner.nextInt());
        System.out.println(scanner.next());
        System.out.println(scanner.next());

        scanner.close();
    }

    static void eg2() {
        System.out.println("example-2");

        String  text    = "1 fish 2 fish red fish blue fish";
        Scanner scanner = new Scanner(text);

        scanner.findInLine("(\\d+) fish (\\d+) fish (\\w+) fish (\\w+) fish");
        MatchResult res = s.match();
        for (int i=0; i<=res.groupCount(); i++) {
            System.out.println(res.group(i));
        }

        scanner.close();
    }

    public static void main(String[] args) {
        ScannerEg.eg1();
        Syetem.out.println();
        ScannerEg.eg2();
    }
}