import java.net.*;
import java.io.*;


public class ParseURL {
    public static void main(String... args) throws MalformedURLException {
        URL url = new URL("https://509.qfstudio.net:443/index.php?key=12345&rx=999#TOP");
        
        System.out.println(url);
        System.out.println("PROTO:\t" + url.getProtocol());
        System.out.println("HOST:\t" + url.getHost());
        System.out.println("FILE:\t" + url.getFile());
        System.out.println("PORT:\t" + url.getPort());
        System.out.println("REF:\t" + url.getRef());
        System.out.println("QUERY:\t" + url.getQuery());
    }
}
