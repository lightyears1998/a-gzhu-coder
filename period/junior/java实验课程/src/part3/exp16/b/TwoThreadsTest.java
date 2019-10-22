public class TwoThreadsTest {
    public static void main(String... args) {
        new SimpleThread("#1").start();
        new SimpleThread("#2").start();
    }
}


class SimpleThread extends Thread {
    public SimpleThread(String threadName) {
       super(threadName);
    }

    public void run() {
        for (int i = 1; i <= 10; ++i) {
            System.out.println(getName() + ": " + i);
            try {
                sleep((int)(Math.random() * 1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        System.out.println(getName() + ": Done!");
    }
}
