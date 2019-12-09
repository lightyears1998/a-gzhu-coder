import java.util.Calendar;
import java.util.Scanner;

public class MyCalendar {
    static Calendar cal = Calendar.getInstance();
    static Scanner sc = new Scanner(System.in);
    static int year = 2019, month = 9;

    public static void main(String[] args) {
        queryUser();
        
        System.out.println("==================================================");
        System.out.printf("                   %d年%02d月\n", year, month);
        System.out.println("--------------------------------------------------");
        System.out.println("日\t一\t二\t三\t四\t五\t六");
        
        cal.set(year, month - 1, 1);
        int weekdayOfFristDay = cal.get(Calendar.DAY_OF_WEEK);
        int dayOfMonth = cal.getActualMaximum(Calendar.DAY_OF_MONTH);
        
        for (int i = 1; i < weekdayOfFristDay; ++i) {
            System.out.print("\t");
        }
        
        int currentWeekday = weekdayOfFristDay;
        for (int i = 1; i <= dayOfMonth; ++i, ++currentWeekday) {
            System.out.printf("%2d\t", i);
            if (i != dayOfMonth && currentWeekday % 7 == 0) {
                System.out.println("");
            }
        }
        System.out.println("");

        System.out.println("==================================================");
    }

    static void queryUser() {
        System.out.print("请输入年份：");
        year = sc.nextInt();
        System.out.print("请输入月份：");
        month = sc.nextInt();
    }
}
