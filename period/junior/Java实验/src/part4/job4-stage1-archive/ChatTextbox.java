import java.awt.*;
import javax.swing.*;
import javax.swing.text.*;


/**
 * 封装插入格式化文本功能的控件
 */
public class ChatTextbox extends JScrollPane {
    final static long serialVersionUID = 0xB35AB87EBE4BA35DL;

    private JTextPane textPane = new JTextPane();

    ChatTextbox() {
        this.setViewportView(textPane);
        textPane.setEditable(false);
    }

    public void appendText(String txt) {
        appendText(txt, Color.BLACK);
    }

    public void appendText(String txt, Color color) {
        StyledDocument doc = textPane.getStyledDocument();

        Style style = textPane.addStyle("Color Style", null);
        StyleConstants.setForeground(style, color);
        try {
            doc.insertString(doc.getLength(), txt, style);
        } 
        catch (BadLocationException e) {}
    }
}
