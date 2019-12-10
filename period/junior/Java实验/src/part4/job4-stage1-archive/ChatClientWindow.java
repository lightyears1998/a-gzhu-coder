import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


class ChatClientWindow extends JFrame implements ActionListener {
    static final long serialVersionUID = 0xA02C3B05814A7B8BL;

    static enum UIMode {
        DISCONNECTED, CONNECTING, CONNECTED;
    };

    private ChatClient client;

    private JTextField serverHostnameInput;
    private JTextField serverPortInput;
    private JTextField nicknameInput;
    private JButton connectOrDisconnectServerButton;
    private JTextField chatMessageInput;
    private JButton submitMessageButton;
    private ChatTextbox chatTextbox;

    ChatClientWindow(ChatClient client) {
        this.client = client;

        this.setTitle(ChatApplication.clientTitle);
        this.setLayout(new BorderLayout());

        chatTextbox = new ChatTextbox();
        this.add(chatTextbox, BorderLayout.CENTER);

        JPanel controlPane = new JPanel(new BorderLayout());
        this.add(controlPane, BorderLayout.SOUTH);

        JPanel configPane = new JPanel(new FlowLayout());
        controlPane.add(configPane, BorderLayout.NORTH);
        
        serverHostnameInput = new JTextField("127.0.0.1", 20);
        configPane.add(new JLabel("服务器主机名："));
        configPane.add(serverHostnameInput);

        serverPortInput = new JTextField(Integer.toString(ChatApplicationDefaults.serverPort), 8);
        configPane.add(new JLabel("端口："));
        configPane.add(serverPortInput);

        nicknameInput = new JTextField(12);
        configPane.add(new JLabel("聊天昵称："));
        configPane.add(nicknameInput);

        connectOrDisconnectServerButton = new JButton("连接服务器");
        connectOrDisconnectServerButton.addActionListener(this);
        configPane.add(connectOrDisconnectServerButton);

        JPanel messagePane = new JPanel(new FlowLayout());
        controlPane.add(messagePane, BorderLayout.CENTER);

        chatMessageInput = new JTextField(64);
        messagePane.add(new JLabel("聊天消息："));
        messagePane.add(chatMessageInput);
        
        submitMessageButton = new JButton("发送消息");
        submitMessageButton.addActionListener(this);
        messagePane.add(submitMessageButton);

        this.setUIMode(UIMode.DISCONNECTED);

        this.setSize(ChatApplicationDefaults.clientWindowWidth, ChatApplicationDefaults.clientWindowHeight);
        this.setLocationRelativeTo(null);
        this.setVisible(true); 
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == connectOrDisconnectServerButton) {
            onClickConnectOrDisconnectServerButton();
        } else if (e.getSource() == submitMessageButton) {
            return;
        }
    }

    void onClickConnectOrDisconnectServerButton() {
        String serverHost = serverHostnameInput.getText();
        int serverPort = 0;
        String nickname = nicknameInput.getText();

        if (serverHost.isEmpty()) {
            this.appendText("服务器主机地址不能为空。\n", Color.ORANGE);
            return;
        }

        if (serverPortInput.getText().isEmpty()) {
            this.appendText("服务器端口不能为空。\n", Color.ORANGE);
            return;
        }

        try {
            serverPort = Integer.parseInt(serverPortInput.getText());
            if (serverPort < 1025 || serverPort > 65535) {
                throw new NumberFormatException();
            }
        } catch (NumberFormatException e) {
            this.appendText("服务器端口不合法，合法的端口为1025~65535范围内的数字。\n", Color.ORANGE);
            return;
        }

        if (nickname.isEmpty()) {
            this.appendText("用户昵称不能为空。\n", Color.ORANGE);
            return;
        }

        client.connectServer(serverHost, serverPort, nickname);
        
        this.setUIMode(UIMode.CONNECTING);
        this.appendText("尝试连接到服务器……\n", Color.GRAY);
    }

    void setUIMode(UIMode mode) {
        switch (mode) {
            case DISCONNECTED: {
                serverHostnameInput.setEditable(true);
                serverPortInput.setEditable(true);
                nicknameInput.setEditable(true);
                connectOrDisconnectServerButton.setText("连接聊天室");
                connectOrDisconnectServerButton.setEnabled(true);
                chatMessageInput.setEditable(false);
                submitMessageButton.setEnabled(false);
                break;
            }
            case CONNECTING: {
                connectOrDisconnectServerButton.setText("尝试连接中");
                connectOrDisconnectServerButton.setEnabled(false);
                break;
            }
            case CONNECTED: {
                serverHostnameInput.setEditable(false);
                serverPortInput.setEditable(false);
                nicknameInput.setEditable(false);
                connectOrDisconnectServerButton.setText("离开聊天室");
                connectOrDisconnectServerButton.setEnabled(true);
                chatMessageInput.setEditable(true);
                submitMessageButton.setEnabled(true);
                break;
            }
        }
    }

    void lockConfigPane() {
        serverHostnameInput.setEditable(false);
        serverPortInput.setEditable(false);
        connectOrDisconnectServerButton.setEnabled(false);
    }

    void unlockConfigPane() {
        serverHostnameInput.setEditable(false);
        serverPortInput.setEditable(false);
        connectOrDisconnectServerButton.setEnabled(false);
    }

    void lockMessagePane() {
        
    }

    void unlockMessagePane() {

    }

    void appendText(String txt) {
        this.chatTextbox.appendText(txt);
    }

    void appendText(String txt, Color color) {
        this.chatTextbox.appendText(txt, color);
    }
}
