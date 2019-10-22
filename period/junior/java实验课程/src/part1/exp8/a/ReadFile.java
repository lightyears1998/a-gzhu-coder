import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("ReadFile.java"));
        for (String line = br.readLine(); line != null; line = br.readLine()) {
            System.out.println(line);
        }
        br.close();
    }
}
