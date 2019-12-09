import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class MyRandomString {
    public static void main(String[] args) throws IOException {
        ArrayList<String> list = new ArrayList<String>();
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("名单.txt"), "UTF-8"));
        for (String line = in.readLine(); line != null; line = in.readLine()) {
            list.add(line);
        }

        Random rand = new Random();

        int length = list.size();
        int i = rand.nextInt(length), j = rand.nextInt(length), k = rand.nextInt(length);
        while (j == i) {
            j = rand.nextInt(length);
        }
        while (k == j || k == i) {
            k = rand.nextInt(length);
        }

        System.out.printf("%s\n%s\n%s\n", list.get(i), list.get(j), list.get(k));
        in.close();
    }
}
