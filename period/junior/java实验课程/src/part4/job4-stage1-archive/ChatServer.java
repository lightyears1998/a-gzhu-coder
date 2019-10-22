import java.awt.*;
import java.net.*;
import java.util.*;


/**
 * 聊天室应用的服务器端
 */
public class ChatServer {
    public static void main(String... args) {
        new ChatServer();
    }

    private ChatServerWindow window;
    private ServerSocket serverSocket;
    private ArrayList<ChatServerMessageThread> messageThreads;

    ChatServer() {
        window = new ChatServerWindow(this);
        window.appendLog(ChatApplication.serverGreeting);

        messageThreads = new ArrayList<ChatServerMessageThread>();
    }

    /**
     * 启动服务器并监听指定端口。
     * @param port
     * @return 返回服务器是否启动成功。
     */
    synchronized boolean start(int port) {
        try {
            serverSocket = new ServerSocket(port);
        } catch (Exception e) {
            window.appendLog("服务器无法使用" + port + "端口", Color.RED);
            return false;
        }

        new Thread() {
            @Override
            public void run() {
                while (serverSocket != null) {
                    try {
                        Socket clientSocket = serverSocket.accept();
                        ChatServerMessageThread messageThread = new ChatServerMessageThread(clientSocket);
                        messageThreads.add(messageThread);
                        messageThread.start();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();

        window.appendLog("服务器已启动，正在监听" + port + "端口。", Color.GREEN);
        return true;
    }

    /**
     * 停止服务器。
     * @return 总是返回true，表示服务器已经成功停止。
     */
    synchronized boolean stop() {
        if (serverSocket != null) {
            try {
                serverSocket.close();
                window.appendLog("服务器已停止。", Color.RED);
                serverSocket = null;
            } catch (Exception e) {
                window.appendLog(e.toString(), Color.YELLOW);
            }
        }
        return true;
    }

    /**
     * 返回服务器是否处于监听状态。
     * @return
     */
    boolean isStarted() {
        return serverSocket != null;
    }
}
