import java.io.*;
import java.net.*;
import java.util.*;


public class ServerItem {
    public static void main(String... args) {
        ServerSocket serverSocket;

        try {
            serverSocket = new ServerSocket(4431);
            System.out.println("服务器启动。");
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }

        while (true) {
            Socket clientSocket = null;

            try {
                System.out.println("正在等待客户……");
                clientSocket = serverSocket.accept();
                System.out.println("客户的地址：" + clientSocket.getInetAddress());
            } catch (Exception e) {
                e.printStackTrace();
                break;
            }

            if (clientSocket != null) {
                new ServerThread(clientSocket).start();
            }
        }
        
        try {
            serverSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("服务器关闭。");
    }
}


class ServerThread extends Thread {
    Socket clientSocket;
    DataInputStream in;
    DataOutputStream out;

    ServerThread(Socket clientSocket) {
        this.clientSocket = clientSocket;
        
        try {
            this.in = new DataInputStream(clientSocket.getInputStream());
            this.out = new DataOutputStream(clientSocket.getOutputStream());
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void run() {
        try {
            String input = in.readUTF();
            Scanner scanner = new Scanner(input);
            scanner.useDelimiter("[^\\d.]+");

            if (input.startsWith("账单：")) {
                double sum = 0;
                while (scanner.hasNext()) {
                    try {
                        double price = scanner.nextDouble();
                        sum += price;
                        System.out.println("读取到客户的单项账单金额：" + price);
                    } catch (InputMismatchException e) {
                        break;
                    }
                }

                System.out.println("客户账单总额：" + sum);

                out.writeUTF("您的账单：");
                out.writeUTF(input);
                out.writeUTF("总额：" + sum + "元");

                scanner.close();
                System.out.println("已处理客户。");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
