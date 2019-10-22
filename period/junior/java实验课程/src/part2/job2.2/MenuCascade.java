import java.awt.*;
import javax.swing.*;


public class MenuCascade {
    public static void main(String[] args) {
        JFrame window = new JFrame("Menu");

        JMenuBar menuBar = new JMenuBar();
        menuBar.add(new JMenu("File"));
        JMenu formatMenu = new JMenu("Format");
        menuBar.add(formatMenu);
        menuBar.add(new JMenu("Help"));
        window.setJMenuBar(menuBar);

        formatMenu.add(new JMenuItem("中文"));
        JMenu radixMenu = new JMenu("进制");
        formatMenu.add(radixMenu);
        radixMenu.add(new JMenuItem("二进制"));
        radixMenu.add(new JMenuItem("八进制"));
        radixMenu.add(new JMenuItem("十进制"));

        window.pack();
        window.setVisible(true);
        window.setSize(400, 240);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
