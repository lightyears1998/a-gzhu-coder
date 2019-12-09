import java.awt.*;
import java.util.*;


/**
 * 聊天室应用的客户端
 */
public class ChatClient {
    public static void main(String... args) {
        new ChatClient();
    }

    private ChatClientWindow window;
    private Messenger messenger;
    private String nickname;


    ChatClient() {
        window = new ChatClientWindow(this);
    }


    /**
     * 返回客户端是否连接到了聊天室。
     * 
     * @return 若连接到聊天室，返回true。
     */
    public boolean isConnected() {
        return messenger != null && messenger.isConnected();
    }


    /**
     * 使用指定参数连接聊天室。
     * 
     * @param hostname 聊天室主机名
     * @param port 聊天室监听端口
     * @param nickname 连接聊天室时使用的昵称
     */
    public synchronized void connect(String hostname, int port, String nickname) {
        if (!isConnected()) {
            this.nickname = nickname;

            ChatClient thisClient = this;
            new Thread() {
                @Override
                public void run() {
                    try {
                        messenger = new Messenger(Messenger.WorkMode.CLIENT, hostname, port, nickname);
                        thisClient.handshake();
                        thisClient.receiveAndHandleMessages();
                    } catch(MessengerFailException e) {
                        thisClient.handleMessengerFailException(e);
                    }
                }
            }.start();
        }
    }

    
    /**
     * `connect()`过程中与服务器进行握手的过程。
     * 
     * 向服务器发送NicknameLoginMessage，若服务器同意本次登录则返回NicknameLoginAcceptedMessage；
     * 否则返回NicknameLoginReejctedMessage。
     */
    private void handshake() throws MessengerFailException {
        assert(isConnected());

        messenger.send(new NicknameLoginMessage(this.nickname));
        Message response = messenger.receive();

        if (response instanceof NicknameLoginAcceptedMessage) {
            window.setUIMode(ChatClientWindow.UIMode.CONNECTED);
        } else {
            disconnect();
            window.showText("昵称已被占用，请更换一个昵称后再试。\n", Color.ORANGE);
            window.setUIMode(ChatClientWindow.UIMode.DISCONNECTED);
        }
    }


    /**
     * 断开与服务器的连接。
     */
    public synchronized void disconnect() {
        if (isConnected()) {
            try {
                messenger.disconnect();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        messenger = null;
    }


    /**
     * 向服务器发送一条聊天消息。
     * 
     * @param content 聊天消息的内容
     */
    public void sendChatMessage(String content) {
        try {
            messenger.send(new ChatMessage(nickname, content));
        } catch (MessengerFailException e) {
            this.handleMessengerFailException(e);
        }
    }

    
    /**
     * 处理消息在网络上传输时产生的异常。
     */
    public synchronized void handleMessengerFailException(MessengerFailException e) {
        e.printStackTrace();

        if (isConnected()) {
            disconnect();
            window.showText("与服务器已断开连接。\n", Color.RED);
            window.setUIMode(ChatClientWindow.UIMode.DISCONNECTED);  
        }
    }

    
    /**
     * 接收并处理服务器传送的消息。
     */
    private void receiveAndHandleMessages() throws MessengerFailException {
        while (isConnected()) {
            Message message = messenger.receive();
            switch (message.getClass().getSimpleName()) {
                case "ChatMessage": {
                    handleChatMessage((ChatMessage)message);
                    break;
                }
                case "NicknameLoginMessage": {
                    handleNicknameLoginMessage((NicknameLoginMessage)message);
                    break;
                }
                case "NicknameLogoutMessage": {
                    handleNicknameLogoutMessage((NicknameLogoutMessage)message);
                    break;
                }
            }
        }
    }


    /**
     * 将聊天消息显示在窗口上。
     */
    private void handleChatMessage(ChatMessage message) {
        Color senderColor = Colorful.getColorFromString(message.sender);
        window.showText(message.sender, senderColor);
        window.showText("在" + message.sentDate.toString() + "时说：\n");
        window.showText("　　" + message.content + "\n");
    }


    /**
     * 显示某位用户的登陆消息。
     */
    private void handleNicknameLoginMessage(NicknameLoginMessage message) {
        Color nicknameColor = Colorful.getColorFromString(message.nickname);
        window.showText(message.nickname, nicknameColor);
        window.showText("在" + new Date().toString() + "时进入了聊天室。\n");
    }


    /**
     * 显示某位用户的离开消息。
     */
    private void handleNicknameLogoutMessage(NicknameLogoutMessage message) {
        Color nicknameColor = Colorful.getColorFromString(message.nickname);
        window.showText(message.nickname, nicknameColor);
        window.showText("在" + new Date().toString() + "时离开了聊天室。\n");
    }
}
