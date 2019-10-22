import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MenuTest {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Window with Menu");
        JMenuBar menuBar = new JMenuBar();
        frame.setJMenuBar(menuBar);

        JMenu menu1 = new JMenu("File");
        JMenu menu2 = new JMenu("Edit");
        JMenu menu3 = new JMenu("Help");
        menuBar.add(menu1);
        menuBar.add(menu2);
        menuBar.add(menu3);

        menu1.add(new JMenuItem("New"));
        menu1.add(new JMenuItem("Save"));
        menu1.add(new JMenuItem("Load"));
        menu1.addSeparator();
        menu1.add(new JMenuItem("Quit"));

        frame.pack();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
