/**
 * GuessNumber.java
 */

import java.util.Scanner;
import java.util.Random;

public class GuessNumber {
    private static Scanner in = new Scanner(System.in);
    
    public static void main(String args[]) {
        System.out.println("猜数字游戏\n");
        
        do {
            play();
        } while (resume());

        System.out.println("再见！");
    }

    // 与用户进行猜数字游戏。
    private static void play() {
        int guessCount = 0;  // 储存用户猜测的次数

        // 生成[1, 100]的随机数。
        Random rand = new Random();
        int randNum = 1 + rand.nextInt(100);
        
        System.out.println("我已经想好一个1~100之间的数字，请输入一个数字：");

        while (in.hasNext()) {
            try {
                // 获取用户的输入。
                String line = in.nextLine();
                int guessNum = Integer.parseInt(line);

                guessCount++;
                
                // 根据用户的猜测给出提示。
                if (guessNum < randNum) {
                    System.out.println("猜的数字太小，请再猜一次。");
                } else if (guessNum > randNum) {
                    System.out.println("猜的数字太大，请再猜一次。");
                } else {
                    System.out.println("恭喜你猜对啦！");
                    System.out.println("你已经猜了" + guessCount + "次。");
                    return;
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("请不要输入一些我不懂的东西哦。");
            }
        }
    }

    // 询问用户是否再来一局。
    private static boolean resume() {
        System.out.println("再来一局吗？[y/n]");
        
        while (in.hasNext()) {
            try {
                String line = in.nextLine().toLowerCase();
                if (line.equals("y")) {
                    return true;
                } else if (line.equals("n")) {
                    return false;
                }
                throw new Exception("用户输入不合法。");
            }
            catch (Exception e) {
                e.printStackTrace();
                System.out.println("请不要输入一些我不懂的东西哦。");
            }
        }
        return false;
    }
}
