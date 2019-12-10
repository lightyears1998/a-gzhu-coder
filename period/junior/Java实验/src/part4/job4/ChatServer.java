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
    private java.util.List<Messenger> clientMessengers;


    ChatServer() {
        window = new ChatServerWindow(this);
        clientMessengers = Collections.synchronizedList(new ArrayList<Messenger>());

        window.showLog(ChatApplication.serverGreeting);
    }


    /**
     * 返回服务器是否处于监听状态。
     * 
     * @return
     */
    boolean isStarted() {
        return serverSocket != null && serverSocket.isBound();
    }


    /**
     * 启动服务器并监听指定端口。
     * 
     * @param port
     * @return 返回服务器是否启动成功。
     */
    synchronized boolean start(int port) {
        try {
            serverSocket = new ServerSocket(port);
        } catch (Exception e) {
            window.showLog("服务器无法使用" + port + "端口", Color.RED);
            return false;
        }

        ChatServer thisServer = this;
        new Thread() {
            @Override
            public void run() {
                while (isStarted()) {
                    try {
                        Socket clientSocket = serverSocket.accept();
                        Messenger messenger = new Messenger(Messenger.WorkMode.SERVER, clientSocket);
                        thisServer.handshake(messenger);
                        thisServer.hearFromClient(messenger);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();

        window.showLog("服务器已启动，正在监听" + port + "端口。", Color.GREEN);
        return true;
    }


    /**
     * 停止服务器。
     */
    synchronized void stop() {
        if (serverSocket != null) {
            try {
                for (Messenger messenger : clientMessengers) {
                    messenger.disconnect();
                }
                clientMessengers.clear();
                serverSocket.close();                
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        serverSocket = null;
        window.showLog("服务器已停止。", Color.RED);
    }


    /**
     * 与某个特定的客户端的握手过程。
     * 
     * 握手过程中若出现任何异常，则拒绝该客户端的连接。
     */
    public synchronized void handshake(Messenger messenger) {
        synchronized (clientMessengers) {
            try {
                window.showLog("正在与" + messenger.getSocketDescription()  + "进行握手。");
    
                NicknameLoginMessage loginMessage = (NicknameLoginMessage)messenger.receive();
                messenger.setNickname(loginMessage.nickname);
                if (nicknameConflicts(messenger.getNickname())) {
                    messenger.send(new NicknameLoginRejectedMessage());
                    window.showLog("因昵称冲突而拒绝了" + messenger.getSocketDescription()  + "的登录。");
                } else {
                    messenger.send(new NicknameLoginAcceptedMessage());
                    window.showLog("接受了" + messenger.getSocketDescription()  + "的登录。");
                    clientMessengers.add(messenger);
                    boardcastMessage(loginMessage);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }


    /**
     * 持续从客户端接收消息。
     */
    public void hearFromClient(Messenger clientMessenger) {
        ChatServer thisServer = this;
        new Thread() {
            @Override
            public void run() {
                while (clientMessenger.isConnected()) {
                    try {
                        Message message = clientMessenger.receive();
                        thisServer.handleMessage(message);
                    } catch (MessengerFailException e) {
                        thisServer.handleMessengerFailException(e);
                    }
                }
            }
        }.start();
    }


    /**
     * 与指定的客户端断开连接。
     */
    private synchronized void disconnectClient(Messenger clientMessenger) {
        synchronized (clientMessengers) {
            if (clientMessenger != null) {
                String clientDescription = clientMessenger.getSocketDescription(); 
                String clientNickname = clientMessenger.getNickname();
                boolean boardcastFlag = clientMessengers.contains(clientMessenger);
    
                clientMessenger.disconnect();
                clientMessengers.remove(clientMessenger);
                if (boardcastFlag) {
                    boardcastMessage(new NicknameLogoutMessage(clientNickname));
                }
                window.showLog("断开了" + clientDescription + "的连接。");
            }
        }
    }


    /**
     * 断开与Nickname对应的客户端的连接。
     */
    public void disconnectClientWithNickname(String nickname) {
        Messenger messenger = getMessengerByNickname(nickname);
        if (messenger != null) {
            disconnectClient(messenger);
        }
    }


    /**
     * 获取Nickname对应的MessageThread。
     */
    private Messenger getMessengerByNickname(String nickname) {
        for (Messenger messenger : clientMessengers) {
            if (messenger.getNickname().equals(nickname)) {
                return messenger;
            }
        }
        return null;
    }


    /**
     * 返回Nickname是否与现有Nickname冲突。
     * 
     * @return 若冲突，返回true。
     */
    public boolean nicknameConflicts(String nickname) {
        for (Messenger messenger : clientMessengers) {
            if (messenger.getNickname().equals(nickname)) {
                return true;
            }
        }
        return false;
    }


    /**
     * 处理某个Messenger产生的异常。
     */
    public void handleMessengerFailException(MessengerFailException e) {
        disconnectClient(e.source);
    }


    /**
     * 处理从某一个客户端收到的消息。
     * 
     * 每收到一个聊天消息，就向已连接的全体客户端广播这个消息。
     * @param message
     */
    public void handleMessage(Message message) {
        switch (message.getClass().getSimpleName()) {
            case "NicknameLogoutMessage": {
                disconnectClientWithNickname(((NicknameLogoutMessage)message).nickname);
                return;
            }
        }

        boardcastMessage(message);
    }


    /**
     * 向所有已连接的客户端广播消息。
     */
    public void boardcastMessage(Message message) {
        for (Messenger messenger : clientMessengers) {
            try {
                messenger.send(message);
            } catch (MessengerFailException e) {
                handleMessengerFailException(e);
            }
        }
    }
}
