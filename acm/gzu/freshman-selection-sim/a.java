import java.util.Scanner;
import java.math.BigDecimal;

public class Main
{
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        while (s.hasNext())
        {
            BigDecimal a = new BigDecimal(s.next());
            BigDecimal b = new BigDecimal(s.next());
            System.out.println(a.add(b));
        }
    }
}
