import javax.swing.*;
import java.util.Random;


public class WordThread extends Thread {
    // Unicode表19968~32320位置上的汉字。
    final int startPosition = 19968;
    final int endPosition = 32320;
    
    int flushInterval = 6000;

    char word;
    JTextField wordField;
    
    WordThread(JTextField wordField, int flushInterval) {
        this.wordField = wordField;
        this.wordField.setEditable(false);
        this.flushInterval = flushInterval;
    }

    public void run() {
        while (true) {
            int pos = startPosition + new Random().nextInt(endPosition - startPosition);
            word = (char)pos;
            wordField.setText(Character.toString(word));

            try {
                sleep(flushInterval);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
