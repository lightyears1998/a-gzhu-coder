import javax.swing.*;
import java.awt.*;

public class TestFlowLayout {
    public static void main(String[] args) {
        JFrame f = new JFrame("Frame Layout");
        JButton button1 = new JButton("确定");
        JButton button2 = new JButton("打开");
        JButton button3 = new JButton("关闭");
        JButton button4 = new JButton("取消");
        f.setLayout(new FlowLayout());

        f.add(button1);
        f.add(button2);
        f.add(button3);
        f.add(button4);

        f.setSize(100, 100);
        f.setVisible(true);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
