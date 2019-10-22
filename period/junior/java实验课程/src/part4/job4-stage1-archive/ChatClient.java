import java.awt.*;
import java.security.*;


/**
 * 聊天室应用的客户端
 */
public class ChatClient {
    public static void main(String... args) {
        new ChatClient();
    }

    private ChatClientWindow window;
    private ChatClientMessageThread messageThread;

    ChatClient() {
        window = new ChatClientWindow(this);
    }

    /**
     * 使用指定参数连接服务器。
     * @param hostname 服务器主机名
     * @param port 服务器监听端口
     * @param nickname 连接服务器时使用的昵称
     * @return 连接服务器是否成功
     */
    synchronized void connectServer(String hostname, int port, String nickname) {
        if (messageThread == null) {
            try {
                messageThread = new ChatClientMessageThread(this, hostname, port, nickname);
                messageThread.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 断开与服务器的连接。
     */
    synchronized void disconnectServer() {
        if (messageThread != null) {
            try {
                messageThread.disconnect();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        messageThread = null;
    }

    /**
     * 返回客户端是否连接到了服务器。
     */
    boolean isConnected() {
        return messageThread != null;
    }

    /**
     * 处理连接失败的情况。
     */
    void handleConnectionFailure() {
        disconnectServer();
        window.appendText("连接失败。\n", Color.RED);
        window.setUIMode(ChatClientWindow.UIMode.DISCONNECTED);
    }

    
    /**
     * 处理服务器发送的聊天消息。
     * @param message
     */
    void handleChatMessage(ChatMessage message) {

    }

    void appendChatMessage(ChatMessage message) {
        Color senderColor = getColorFromStringHash(message.sender);
        window.appendText(message.sender, senderColor);
        window.appendText("在" + message.sentDate.toString() + "时说：\n");
        window.appendText("　　" + message.content + "\n");
    }

    Color getColorFromStringHash(String str) {
        int r = 0, g = 0, b = 0;
        try {
            byte[] bytes = MessageDigest.getInstance("MD2").digest(str.getBytes());
            r = Byte.toUnsignedInt(bytes[0]);
            g = Byte.toUnsignedInt(bytes[1]);
            b = Byte.toUnsignedInt(bytes[2]);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }   
        return new Color(r, g, b);     
    }
}
