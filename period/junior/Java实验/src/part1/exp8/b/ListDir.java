import java.io.File;

public class ListDir {
    public static void main(String args[]) {
        File[] files = new File(".").listFiles();
        for (File file : files) {
            if (file.isDirectory()) {
                System.out.println("<DIR>" + file.getName());
            } else {
                System.out.println(file.getName());
            }
        }
    }
}
