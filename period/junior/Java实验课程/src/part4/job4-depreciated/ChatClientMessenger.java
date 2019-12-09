import java.net.*;
import java.io.*;


/**
 * 客户端与服务器的消息通信代理
 */
class ChatClientMessenger {
    private String nickname;

    private Socket serverSocket;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    ChatClientMessenger(ChatClient client, String serverHostname, int serverPort, String nickname) {
        this.nickname = nickname;

        try {
            serverSocket = new Socket(serverHostname, serverPort);
            
            // 与服务器上建立对象流的顺序相对应：
            // 建立对象流时，要先建立输出流，再建立输入流；调换建立流的顺序会导致两端陷入阻塞。
            // 详见ObjectInputStream/ObjectOutputStream构造函数注释。
            out = new ObjectOutputStream(serverSocket.getOutputStream());
            in = new ObjectInputStream(serverSocket.getInputStream());
            
            // 尝试使用指定昵称连接聊天服务器。
            loginNickname();
        } catch (Exception e) {
            e.printStackTrace();
            this.disconnect();
            
            if (e.getMessage().equals("登录被拒绝。")) {
                // 添加日志
            }
            client.handleConnectionFailure();
        }
    }


    /**
     * 返回是否与服务器建立了连接。
     * @return 若成功与服务器连接，返回true。
     */
    boolean isConnected() {
        return this.serverSocket.isConnected();
    }
    
    
    /**
     * 断开与聊天室服务器的连接。
     */
    public void disconnect() {
        if (serverSocket != null && serverSocket.isConnected()) {
            try {
                out.writeObject(new NicknameLogoutMessage(nickname));
                serverSocket.close();
            } catch(Exception e) {
                e.printStackTrace();
            }    
        }
        serverSocket = null;
    }
    

    public String getNickname() {
        return this.nickname;
    }


    private void loginNickname() throws Exception {
        NicknameLoginMessage loginMessage = new NicknameLoginMessage(nickname);
        out.writeObject(loginMessage);

        Message loginResponse = (Message)in.readObject();
        if (loginResponse instanceof NicknameLoginRejectedMessage) {
            throw new Exception("登录被拒绝。");
        }
    }

    
    /**
     * 向聊天服务器发送一条消息。
     * @param message
     */
    public void send(Message message) throws IOException {
        out.writeObject(message);
    }

    
    /**
     * 从聊天服务器接受一条消息。
     */
    public Message receive() throws IOException, ClassNotFoundException {
        return (Message)in.readObject();
    }
}
