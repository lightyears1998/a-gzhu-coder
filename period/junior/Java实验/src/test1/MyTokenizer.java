import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class MyTokenizer {
    public static void main(String[] args) throws IOException {
        final String seperator = "*";

        int totalPrice = 0;
        BufferedReader in = new BufferedReader(new FileReader("采购清单.txt"));
        for (String line = in.readLine(); line != null; line = in.readLine()) {
            String regex = "[^\\d.]+";
            line = line.replaceAll(regex, seperator);
            
            StringTokenizer scanner = new StringTokenizer(line, seperator);
            int a = Integer.parseInt(scanner.nextToken());
            int b = Integer.parseInt(scanner.nextToken());

            System.out.println(a + " * " + b + " = " + a*b);
            totalPrice += a*b;
        }
        System.out.println("总价：" + totalPrice);
        in.close();
    }
}
