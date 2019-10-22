import javax.swing.*;
import java.awt.*;

public class GridLayoutWindow extends JFrame {
    GridLayoutWindow() {
        setLayout(new GridLayout(3, 2));  // 在3行2列的网格中排列组件
        for (int i = 1; i <= 6; ++i) {
            add(new JButton(new Integer(i).toString()));
        }
    }

    public static void main(String[] args) {
        GridLayoutWindow window = new GridLayoutWindow();
        window.setTitle("GridLayout Application");
        window.pack();
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
