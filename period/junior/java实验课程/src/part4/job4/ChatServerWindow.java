import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;


/**
 * 服务器端窗口
 */
class ChatServerWindow extends JFrame {
    static final long serialVersionUID = 0x01C4AD270344EB15L;

    private ChatTextbox logPane;

    
    ChatServerWindow(ChatServer server) {
        this.setTitle(ChatApplication.serverTitle);
        this.setLayout(new BorderLayout());

        logPane = new ChatTextbox();
        this.add(logPane, BorderLayout.CENTER);

        JPanel controlPanel = new JPanel(new FlowLayout());
        controlPanel.add(new JLabel("服务器监听端口："));

        JTextField portField = new JTextField(Integer.toString(ChatApplicationDefaults.serverPort), 8);
        controlPanel.add(portField);
        
        JButton startOrStopServerButton = new JButton("启动服务器");
        startOrStopServerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (server.isStarted()) {
                    server.stop();
                    startOrStopServerButton.setText("启动服务器");
                } else {
                    int port = 0;

                    try {
                        port = Integer.parseInt(portField.getText());
                    } catch (NumberFormatException err) {
                        showLog("端口必须为数字。", Color.RED);
                    }

                    if (port < 1025 || port > 65535) {
                        showLog("指定的端口不合法，合法的端口范围是1025~65535。", Color.RED);
                        return;
                    }

                    boolean serverOK = server.start(port);
                    if (serverOK) {
                        startOrStopServerButton.setText("停止服务器");
                    }
                }
            }
        });
        controlPanel.add(startOrStopServerButton);

        this.add(controlPanel, BorderLayout.SOUTH);

        this.setSize(ChatApplicationDefaults.serverWindowWidth, ChatApplicationDefaults.serverWindowHeight);
        this.setLocationRelativeTo(null);
        this.setVisible(true); 
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }


    /**
     * 在日志窗口显示一条日志。
     * 
     * @param log 日志
     */
    void showLog(String log) {
        this.showLog(log, Color.BLACK);
    }


    /**
     * 在日志窗口显示一条带颜色的日志。
     * 
     * @param log 日志
     * @param color 日志颜色
     */
    void showLog(String log, Color color) {
        logPane.appendText(new Date().toString() + ": " + log + "\n", color);
    }
}
