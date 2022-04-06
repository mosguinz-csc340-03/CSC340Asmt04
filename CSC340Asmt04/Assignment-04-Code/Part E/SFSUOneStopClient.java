package assignment04PartE;

/**
 *
 * Part E
 *
 * Please do not change any code in this file.
 *
 */

import java.util.PriorityQueue;

public class SFSUOneStopClient {

    public static void main(String[] args) {

        System.out.println("-------------------------------------------------------------");
        System.out.println("\t\t\t SFSU ONE STOP STUDENT SERVICES CENTER");
        System.out.println("-------------------------------------------------------------");

        Student[] students = {
                new Student("Mickey", "Mouse", 1002, 3.7, 1, 17),
                new Student("Minnie", "Mouse", 1001, 3.9, 10, 15),
                new Student("Goofy", "Dog", 1007, 2.3, 17, 1),
                new Student("Pluto", "Dog", 1005, 3.7, 7, 17),
                new Student("Milo", "Dog", 1004, 3.7, 7, 17),
                new Student("Donald", "Duck", 1006, 3.1, 5, 2),
                new Student("Daisy", "Duck", 1003, 1.7, 1, 17),
        };

        PriorityQueue<Student> oneStopPQ = new PriorityQueue<Student>();

        for (String priority : Student.getPriorities()) {
            Student.setCompareToPriority(priority);
            if (!oneStopPQ.isEmpty()) {
                oneStopPQ.clear();
            }
            for (Student student : students) {
                oneStopPQ.add(student);
            }
            SFSUOneStop.display(oneStopPQ, priority);
        }

        oneStopPQ.clear();
    }
}