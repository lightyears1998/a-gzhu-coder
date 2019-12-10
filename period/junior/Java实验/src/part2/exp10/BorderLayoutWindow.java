import javax.swing.*;
import java.awt.*;

public class BorderLayoutWindow extends JFrame {
    public BorderLayoutWindow() {
        setLayout(new BorderLayout());
        add(new JButton("North"), BorderLayout.NORTH);
        add(new JButton("South"), BorderLayout.SOUTH);
        add(new JButton("West"), BorderLayout.WEST);
        add(new JButton("East"), BorderLayout.EAST);
        add(new JButton("Center"), BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        BorderLayoutWindow window = new BorderLayoutWindow();
        window.setTitle("BorderLayout Application");
        window.pack();
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
