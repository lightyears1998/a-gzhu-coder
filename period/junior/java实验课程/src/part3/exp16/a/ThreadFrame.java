import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


class ThreadFrame extends JFrame implements ActionListener {
    JTextField wordField, inputField, scoreField;
    JButton button;
    WordThread wordThread;

    int score = 0;

    ThreadFrame() {
        wordField = new JTextField(6);
        wordField.setFont(new Font("", Font.BOLD, 72));
        wordField.setHorizontalAlignment(JTextField.CENTER);

        inputField = new JTextField(10);
        inputField.addActionListener(this);

        scoreField = new JTextField(5);
        scoreField.setEditable(false);
        scoreField.setText("得分：0");

        button = new JButton("开始");
        button.addActionListener(this);

        wordThread = new WordThread(wordField, 5000);

        add(button, BorderLayout.NORTH);
        add(wordField, BorderLayout.CENTER);

        JPanel southPanel = new JPanel();
        southPanel.add(new JLabel("输入汉字（回车）"));
        southPanel.add(inputField);
        southPanel.add(scoreField);
        add(southPanel, BorderLayout.SOUTH);
        
        setBounds(150, 150, 500, 360);
        setVisible(true);
        validate();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == button) {
            if (!(wordThread.isAlive())) {
                wordThread = new WordThread(wordField, 5000);
                try {
                    wordThread.start();
                } catch (Exception exc) {
                    exc.printStackTrace();
                }
            }    
        } else if (e.getSource() == inputField) {
            if (inputField.getText().equals(wordField.getText())) {
                score++;
            }
            System.out.println("Activiating...");
            scoreField.setText("得分：" + score);
            inputField.setText("");
        }
    }
}
