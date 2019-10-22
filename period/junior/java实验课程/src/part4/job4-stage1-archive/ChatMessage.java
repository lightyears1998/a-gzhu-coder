import java.io.*;
import java.util.*;


/**
 * 服务器与客户端之间传递消息的公共基类
 */
class Message implements Serializable {
    final static long serialVersionUID = 0xEAF24721CC7A9F01L;
}


/**
 * 客户端之间的聊天消息
 */
class ChatMessage extends Message implements Serializable {
    final static long serialVersionUID = 0x0E3A4BB9F7344E253L;

    public String sender;  // 消息的发送方
    public Date sentDate;  // 消息发送的时间
    public String content; // 消息的内容
    
    public ChatMessage(String sender, String content) {
        this.sender = sender;
        this.sentDate = new Date();
        this.content = content;
    }
}


/**
 * 客户端发送的昵称登录消息
 */
class NicknameLoginMessage extends Message implements Serializable {
    final static long serialVersionUID = 0x9E11DA1DFB66BEDAL;

    public String nickname;

    NicknameLoginMessage(String nickname) {
        this.nickname = nickname;
    }
}


/**
 * 服务器端在接受客户端昵称登录请求时发送的消息
 */
class NicknameLoginAcceptedMessage extends Message implements Serializable {
    final static long serialVersionUID = 0xAC4A3CD4D1DB047DL;
}


/**
 * 服务器端在拒绝客户端昵称登录请求时发送的消息
 */
class NicknameLoginRejectedMessage extends Message implements Serializable {
    final static long serialVersionUID = 0xB41FC5354327354BL;
}


/**
 * 客户端发送的昵称注销消息
 */
class NicknameLogoutMessage extends Message implements Serializable {
    final static long serialVersionUID = 0xC08A44F095C06D66L;

    public String nickname;

    NicknameLogoutMessage(String nickname) {
        this.nickname = nickname;
    }
}
