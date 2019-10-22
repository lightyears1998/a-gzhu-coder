import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class ComputerFrame extends JFrame {
    JMenuBar menuBar = new JMenuBar();
    JMenu choiceGrade = new JMenu("选择级别");
    JMenuItem grade1 = new JMenuItem("幼儿级别"), 
        grade2 = new JMenuItem("儿童级别");
    JTextField text1 = new JTextField(5), 
        text2 = new JTextField(5),  // 可见字长为5
        textResult = new JTextField(5);
    JButton getProblem = new JButton("获取题目"), 
        giveAnswer = new JButton("确认答案");
    JLabel operationLabel = new JLabel("?"),
        messageLabel = new JLabel("请选择级别并获取题目。");
    Teacher teacherZhang = new Teacher(operationLabel, messageLabel, text1, text2, textResult);

    ComputerFrame() {
        setLayout(new FlowLayout());
        setJMenuBar(menuBar);

        menuBar.add(choiceGrade);
        choiceGrade.add(grade1);
        choiceGrade.add(grade2);
        
        add(text1);
        add(operationLabel);
        add(text2);
        add(new JLabel("="));
        add(textResult);
        add(giveAnswer);
        add(messageLabel);
        add(getProblem);

        grade1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                teacherZhang.setMaxInteger(10);
            }
        });

        grade2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                teacherZhang.setMaxInteger(50);
            }
        });

        text1.setEditable(false);
        text2.setEditable(false);

        getProblem.setActionCommand("getProblem");
        getProblem.addActionListener(teacherZhang);
        giveAnswer.setActionCommand("answer");
        giveAnswer.addActionListener(teacherZhang);
    }
}
