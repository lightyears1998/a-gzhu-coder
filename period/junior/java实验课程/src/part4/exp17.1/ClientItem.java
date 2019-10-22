import java.io.*;
import java.net.*;
import java.util.*;


public class ClientItem {
    public static void main(String... args) {
        Scanner scanner = new Scanner(System.in);
        Socket socket = null;

        try {
            socket = new Socket();
            
            System.out.println("输入服务器的IP：");
            String IP = scanner.nextLine();

            System.out.println("输入服务器的端口号：");
            int port = scanner.nextInt();

            scanner.nextLine();  // 消耗回车

            InetAddress address = InetAddress.getByName(IP);
            InetSocketAddress socketAddress = new InetSocketAddress(address, port);
            
            socket.connect(socketAddress);      

            Worker worker = new Worker();
            worker.setDataInputStream(new DataInputStream(socket.getInputStream()));
            worker.setDataOutputStream(new DataOutputStream(socket.getOutputStream()));
            Thread workerThread = new Thread(worker);
            
            workerThread.start();

        } catch (SocketException e) {
            System.out.println("服务器已断开：" + e);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


class Worker implements Runnable {
    Scanner scanner = new Scanner(System.in);
    DataInputStream in;
    DataOutputStream out;
    
    public void setDataInputStream(DataInputStream in) {
        this.in = in;
    }

    public void setDataOutputStream(DataOutputStream out) {
        this.out = out;
    }

    public void run() {
        System.out.println("输入账单：");
        String content = scanner.nextLine();

        try {
            out.writeUTF("账单：" + content);
            String str;
            
            for (int i = 1; i <=3; ++i) {
                str = in.readUTF();
                System.out.println(str);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
