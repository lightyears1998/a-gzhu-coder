import java.awt.*;
import javax.swing.*;


public class LoginWindow {
    public static void main(String[] args) {
        JFrame window = new JFrame("登录");
        window.setLayout(new GridLayout(4, 1));

        JPanel panelA = new JPanel(new FlowLayout());
        panelA.add(new JLabel("用户名："));
        panelA.add(new JTextField(20));
        window.add(panelA);

        JPanel panelB = new JPanel(new FlowLayout());
        panelB.add(new JLabel("密　码："));
        panelB.add(new JPasswordField(20));
        window.add(panelB);

        JPanel panelC = new JPanel(new FlowLayout());
        panelC.add(new JButton("确定"));
        window.add(panelC);

        window.pack();
        window.setVisible(true);
        window.setSize(400, 200);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
