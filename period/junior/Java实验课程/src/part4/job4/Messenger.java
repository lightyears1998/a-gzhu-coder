import java.net.*;
import java.io.*;


/**
 * 客户端与服务器的消息通信代理
 */
public class Messenger {
    static enum WorkMode {
        SERVER, CLIENT
    };

    private String nickname;

    private Socket socket;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    
    Messenger(WorkMode mode, Socket socket) throws MessengerFailException {
        try {
            this.socket = socket;
            establishStreams(mode);
        } catch (Exception e) {
            throw raise(e);
        }
         
    }


    Messenger(WorkMode mode, String hostname, int port, String nickname) throws MessengerFailException {
        try {
            this.socket = new Socket(hostname, port);
            this.nickname = nickname;
            establishStreams(mode);
        } catch (Exception e) {
            throw raise(e);
        }
    }


    /**
     * 建立ObjectInputStream和ObjectOutputStream
     */
    private void establishStreams(WorkMode mode) throws IOException {
        // 客户端与服务建立对象流的顺序相对应，
        // 若一端先建立输入流，则另一端先建立输出流。
        // 详见ObjectInputStream/ObjectOutputStream构造函数注释。
        switch (mode) {
            case CLIENT: {
                out = new ObjectOutputStream(socket.getOutputStream());
                in = new ObjectInputStream(socket.getInputStream());
                break;
            }
            case SERVER: {
                in = new ObjectInputStream(socket.getInputStream());
                out = new ObjectOutputStream(socket.getOutputStream());
                break;
            }
        }
    }

    
    public void setNickname(String nickname) {
        this.nickname = nickname;
    }


    public String getNickname() {
        return nickname;
    }


    public String getSocketDescription() {
        return socket.getInetAddress().toString() + ":" + socket.getPort() + "[" + nickname + "]";
    }


    /**
     * 返回是否成功建立了连接。
     * @return 若连接成功，返回true。
     */
    boolean isConnected() {
        return socket != null && socket.isConnected();
    }
    

    /**
     * 断开连接。
     */
    public void disconnect() {
        if (socket != null && socket.isConnected()) {
            try {
                out.writeObject(new NicknameLogoutMessage(nickname));
                socket.close();
            } catch(Exception e) {
                e.printStackTrace();
            }    
        }
        socket = null;
    }


    /**
     * 发送一条消息。
     */
    public void send(Message message) throws MessengerFailException {
        try {
            out.writeObject(message);    
        } catch (Exception e) {
            throw raise(e);
        }
    }

    
    /**
     * 接收一条消息。
     */
    public Message receive() throws MessengerFailException {
        try {
            Message message = (Message)in.readObject();
            return message;
        } catch (Exception e) {
            throw raise(e);
        }
    }

    
    /**
     * 包装异常。
     */
    private MessengerFailException raise(Exception e) {
        return new MessengerFailException(this, e);
    }
}


/**
 * 消息传递过程中的异常
 */
class MessengerFailException extends Exception {
    final static long serialVersionUID = 0x140C2BDFACB72301L;

    /** 产生异常的Messenger实例 */
    public Messenger source; 

    /** 引发MessengerFailException的内部异常 */
    public Exception innerException;

    MessengerFailException(Messenger source, Exception innerException) {
        this.source = source;
        this.innerException = innerException;
    }
}
