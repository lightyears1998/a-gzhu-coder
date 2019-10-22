import java.net.*;
import java.io.*;


/**
 * 服务器端用于接受客户端发送的消息的线程
 */
class ChatServerMessageThread extends Thread {
    ChatServer server;
    Socket clientSocket;
    
    ObjectInputStream in;
    ObjectOutputStream out;

    String clientNickname;

    ChatServerMessageThread(ChatServer server, Socket clientSocket) {
        this.server = server;
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            // 与客户端上建立对象流的顺序相对应：
            // 建立对象流时，要先建立输入流，再建立输出流；调换建立流的顺序会导致两端陷入阻塞。
            // 详见ObjectInputStream/ObjectOutputStream构造函数注释。
            in = new ObjectInputStream(clientSocket.getInputStream());
            out = new ObjectOutputStream(clientSocket.getOutputStream());
            
            getNicknameFromClient();
            disconnectIfNicknameConficts();
            receiveMessagesFromClient();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    synchronized public void shutdown() {
        if (clientSocket != null) {
            try {
                clientSocket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        clientSocket = null;
    }

    public boolean sendMessageToClient(Message message) {
        try {
            out.writeObject(message);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public String getClientNickname() {
        return this.clientNickname != null ? this.clientNickname : "";
    }

    private void getNicknameFromClient() throws IOException, ClassNotFoundException {
        NicknameLoginMessage message = (NicknameLoginMessage)in.readObject();
        this.clientNickname = message.nickname;
    }

    private void disconnectIfNicknameConficts() throws IOException, ClassNotFoundException {
        if (server.nicknameConflicts(clientNickname)) {
            out.writeObject(new NicknameLoginRejectedMessage());
            server.getWindow().showLog("正在拒绝同名的连接。");
            server.disconnectClientWithNickname(clientNickname);
        } else {
            out.writeObject(new NicknameLoginAcceptedMessage());
            server.handleMessage(new NicknameLoginMessage(clientNickname));
        }
    }

    private void receiveMessagesFromClient() throws IOException, ClassNotFoundException {
        while (clientSocket != null) {
            Message nextMessage = (Message)in.readObject();
            server.handleMessage(nextMessage);
        }
    }
}
