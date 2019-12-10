public class Hello {
    public static void main(String args[]) {
        System.out.println("Good morning, Zhang!");
        
        Student zhang = new Student();
        zhang.speak();
    }
}

class Student {
    void speak() {
        System.out.println("Morning, I am a student.");
    }
}
