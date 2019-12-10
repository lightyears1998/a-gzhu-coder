import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;


public class Draw extends JFrame implements ActionListener {
    public static final long serialVersionUID = 0x1706300001L;

    JButton startButton;
    JButton stopButton;
    JLabel nameLabel;

    java.util.List<String> drawList;
    boolean isDrawing;

    public static void main(String... args) {
        new Draw();
    }

    public Draw() {
        startButton = new JButton("开始");
        stopButton = new JButton("停止");
        nameLabel = new JLabel("待开始");

        drawList = new ArrayList<String>();
        isDrawing = false;

        setUI();
        readDrawList();
    }

    private void setUI() {
        this.setTitle("抽签");
        this.setLayout(new BorderLayout());
        
        this.setSize(400, 300);
    
        JPanel buttonPanel = new JPanel(new GridLayout(1, 2));
        startButton.addActionListener(this);
        buttonPanel.add(startButton);
        stopButton.addActionListener(this);
        buttonPanel.add(stopButton);
        this.add(buttonPanel, BorderLayout.NORTH);

        nameLabel.setHorizontalAlignment(SwingConstants.CENTER);
        nameLabel.setFont(new Font("SimSun", Font.BOLD, 72));
        this.add(nameLabel, BorderLayout.CENTER);
        
        startButton.setEnabled(true);
        stopButton.setEnabled(false);

        this.setVisible(true);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void readDrawList() {
        try {
            InputStreamReader streamReader = new InputStreamReader(new FileInputStream("DrawList.txt"), "UTF8");
            BufferedReader reader = new BufferedReader(streamReader);
            while (reader.ready()) {
                String nextLine = reader.readLine();
                if (!nextLine.isEmpty()) {
                    drawList.add(nextLine);
                }
            }
            reader.close();
            
            if (drawList.isEmpty()) {
                throw new Exception("抽签列表为空。");
            }
        } catch (Exception e) {
            showDrawListHint();
        }
    }

    private void showDrawListHint() {
        StringBuilder hintBuilder = new StringBuilder();
        hintBuilder.append("请在同级目录下创建UTF8编码的抽签列表DrawList.txt并输入抽签项。\n");
        hintBuilder.append("每个抽签项目请使用换行符隔开。\n");

        JOptionPane.showMessageDialog(null, hintBuilder.toString(), "抽签程序使用提示", JOptionPane.PLAIN_MESSAGE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == startButton) {
            onClickStartButton();
        } else if (e.getSource() == stopButton) {
            onClickStopButton();
        }
    }

    private void onClickStartButton() {
        if (!drawList.isEmpty()) {
            isDrawing = true;
            new Thread() {
                @Override
                public void run() {
                    while (isDrawing) {
                        int randIdx = new Random().nextInt(drawList.size());
                        nameLabel.setText(drawList.get(randIdx));

                        try {
                            sleep(new Random().nextInt(50));
                        } catch (InterruptedException e) {}
                    }
                }
            }.start();
        }
        startButton.setEnabled(false);
        stopButton.setEnabled(true);
    }

    private void onClickStopButton() {
        isDrawing = false;
        startButton.setEnabled(true);
        stopButton.setEnabled(false);
    }
}
