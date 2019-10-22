import java.net.*;
import java.io.*;


/**
 * 服务器端用于接受客户端发送的消息的线程
 */
class ChatServerMessageThread extends Thread {
    Socket clientSocket;
    ObjectInputStream in;
    ObjectOutputStream out;

    String clientNickname;

    ChatServerMessageThread(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            in = new ObjectInputStream(clientSocket.getInputStream());
            out = new ObjectOutputStream(clientSocket.getOutputStream());
            
            getNicknameFromClient();
            receiveMessagesFromClient();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public boolean sendMessageToClient(Message message) {
        try {
            out.writeObject(message);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    public String getClientNickname() {
        return this.clientNickname != null ? this.clientNickname : "";
    }


    private void getNicknameFromClient() {
        try {
            NicknameLoginMessage message = (NicknameLoginMessage)in.readObject();
            out.writeObject(new NicknameLoginRejectedMessage());
        } catch (Exception e) {

        }
    }

    private void receiveMessagesFromClient() throws IOException, ClassNotFoundException {
        while (true) {
            Object nextMessage = in.readObject();
            System.out.println(nextMessage.getClass());
        }
    }
}
