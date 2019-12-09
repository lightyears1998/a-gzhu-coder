import java.util.Random;
import java.awt.event.*;
import javax.swing.*;

class Teacher implements ActionListener {
    Random random = new Random();
    JLabel operationLabel, messageLabel;
    JTextField text1, text2, textResult;
    int maxInteger = 10;
    
    Teacher(JLabel operationLabel, JLabel messageLabel, JTextField text1, JTextField text2, JTextField textResult) {
        this.operationLabel = operationLabel;
        this.messageLabel = messageLabel;
        this.text1 = text1;
        this.text2 = text2;
        this.textResult = textResult;
    }

    void setMaxInteger(int maxInteger) {
        this.maxInteger = maxInteger;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        switch (command) {
            case "getProblem": {
                text1.setText(Integer.toString(random.nextInt(maxInteger) + 1));
                text2.setText(Integer.toString(random.nextInt(maxInteger) + 1));
                if (random.nextDouble() < 0.5) {
                    operationLabel.setText("+");
                } else {
                    operationLabel.setText("-");                     
                }
                messageLabel.setText("请回答。");
                break;
            }
            case "answer": {
                int lhs = Integer.parseInt(text1.getText());
                int rhs = Integer.parseInt(text2.getText());
                int ans = Integer.parseInt(textResult.getText());
                int op = operationLabel.getText() == "+" ? 1 : -1;
                if (lhs + rhs*op == ans) {
                    messageLabel.setText("回答正确！");
                } else {
                    messageLabel.setText("回答错误。");
                }
                break;
            }
        }
    }
}
