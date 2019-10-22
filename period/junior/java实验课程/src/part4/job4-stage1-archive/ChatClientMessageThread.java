import java.net.*;
import java.io.*;


/**
 * 客户端接受服务器发送的消息的线程
 */
class ChatClientMessageThread extends Thread {
    private ChatClient client;
    private String serverHostname;
    private int serverPort;
    private String nickname;

    private Socket serverSocket;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    ChatClientMessageThread(ChatClient client, String serverHostname, int serverPort, String nickname) {
        this.client = client;
        this.serverHostname = serverHostname;
        this.serverPort = serverPort;
        this.nickname = nickname;
    }

    @Override
    public void run() {
        try {
            serverSocket = new Socket(serverHostname, serverPort);
            in = new ObjectInputStream(serverSocket.getInputStream());
            out = new ObjectOutputStream(serverSocket.getOutputStream());

            loginNickname();
            receiveMessageFromServer();
        } catch (Exception e) {
            e.printStackTrace();
            client.handleConnectionFailure();
            client.disconnectServer();
        }
    }

    public void disconnect() {
        if (serverSocket != null) {
            try {
                serverSocket.close();
            } catch(Exception e) {
                e.printStackTrace();
            }
            serverSocket = null;
        } 
    }
    
    private void loginNickname() throws Exception {
        try {
            NicknameLoginMessage loginMessage = new NicknameLoginMessage(nickname);
            out.writeObject(loginMessage);

            Message loginResponse = (Message)in.readObject();
            if (loginResponse instanceof NicknameLoginRejectedMessage) {
                System.out.println(loginResponse.getClass().getSimpleName());
                throw new Exception("登录被拒绝。");
            }
        } catch (Exception e) {
            throw e;
        }
    }

    private void receiveMessageFromServer() throws IOException, ClassNotFoundException {
        while (serverSocket.isConnected()) {
            Object nextMessage = in.readObject();
            switch (nextMessage.getClass().getSimpleName()) {
                case "ChatMessage": {
                    client.handleChatMessage((ChatMessage)nextMessage);
                    break;
                }
            }
        }
    }
}
