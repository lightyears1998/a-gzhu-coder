import java.util.*;

public class StringTokenizerTest {
    public static void main(String[] args) {
        String items = {
            "苹果：56.7元，香蕉：12元，芒果：19.8元",
            "酱油：6.7元，精盐：0.8元，榨菜：9.8元"
        };
        String seperator = "*";

        // 等价于"[^0123456789.]+"
        String regex = "[^\\d.]+";  // 其中“^”是取反而不是匹配开头。
        s1 = s1.replaceAll(regex, seperator);  // 将正则匹配的字串用分隔符替代
        System.out.println(s1);
    }
}
