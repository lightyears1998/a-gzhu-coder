import java.awt.*;
import javax.swing.*;

public class MainClass {
    public static void main(String[] args) {
        ComputerFrame frame = new ComputerFrame();
        frame.setTitle("算术测试");

        frame.pack();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setBounds(100, 100, 650, 180);
    }
}
