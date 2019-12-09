import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TestActionEvent {
    public static void main(String[] args) {
        JFrame f = new JFrame("Test");

        JButton minusBtn = new JButton("-");
        JButton plusBtn = new JButton("+");
        JLabel counterLb = new JLabel("0", JLabel.CENTER);

        Monitor monitor = new Monitor();
        monitor.setCounterLabel(counterLb);
        minusBtn.setActionCommand("-");
        minusBtn.addActionListener(monitor);
        plusBtn.setActionCommand("+");
        plusBtn.addActionListener(monitor);

        f.setLayout(new GridLayout());
        f.add(minusBtn);
        f.add(counterLb);
        f.add(plusBtn);
        f.pack();
        f.setVisible(true);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

class Monitor implements ActionListener {
    int counter = 0;
    JLabel counterLabel;

    public void setCounterLabel(JLabel label) {
        this.counterLabel = label;
    }

    private void updateCounterLabel() {
        if (counterLabel != null) {
            counterLabel.setText(new Integer(counter).toString());
        }
    }

    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        if (command.equals("-")) {
            if (counter > 0) {
                counter--;
            }
        } else if (command.equals("+")) {
            counter++;
        }
        updateCounterLabel();
    }
}
