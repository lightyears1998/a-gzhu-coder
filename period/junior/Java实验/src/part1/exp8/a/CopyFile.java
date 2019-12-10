import java.io.FileInputStream;
import java.io.FileOutputStream;    
import java.io.IOException;;

public class CopyFile {
    public static void main(String args[]) throws IOException {
        FileInputStream in = new FileInputStream("CopyFile.java");
        FileOutputStream out = new FileOutputStream("CopyFile.java.tmp");

        int read = in.read();
        while (read != -1) {
            out.write(read);
            read = in.read();
        }
        
        in.close();
        out.close();
    }    
}
