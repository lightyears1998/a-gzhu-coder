/**
 * SalaryCalculator.java
 */

public class SalaryCalculator {
    public static void main(String args[]) {
        Employee[] employees = {
            new Manager("经理", 9800),
            new Salesman("销售A", 5000, 1200), new Salesman("销售B", 4800, 1400),
            new Worker("工人A", 25), new Worker("工人B", 27), new Worker("工人C", 28)
        };

        for (Employee employee : employees) {
            System.out.println(employee.name + "的工资为：" + employee.ComputeSalary());
        }
    }
}

abstract class Employee {
    String name;
    abstract double ComputeSalary();

    Employee(String name) {
        this.name = name;
    }
}

class Manager extends Employee {
    double salary;
    
    Manager(String name, double salary) {
        super(name);
        this.salary = salary;
    }

    @Override
    double ComputeSalary() {
        return salary;
    }
}

class Salesman extends Employee {
    double basicSalary;
    double bonus;

    Salesman(String name, double basicSalary, double bonus) {
        super(name);
        this.basicSalary = basicSalary;
        this.bonus = bonus;
    }

    @Override
    double ComputeSalary() {
        return basicSalary + bonus;
    }
}

class Worker extends Employee {
    final static double SALARY_PER_DAY = 180;
    
    int workdays;

    Worker(String name, int workdays) {
        super(name);
        this.workdays = workdays;
    }

    @Override
    double ComputeSalary() {
        return workdays * SALARY_PER_DAY;
    }
}
