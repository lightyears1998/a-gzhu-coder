public class MainClass {
    public static void main(String[] args) {
        Teacher teacher = new Teacher();
        Student student = new Student();

        student.speak();
        System.out.printf("%.0f\n", teacher.add(12, 236));
        System.out.printf("%.0f\n", teacher.sub(234, 120));
    }
}
