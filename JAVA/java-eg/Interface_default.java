public class Interface_default {
    interface Younger {
        default void print() {
            System.out.println("I am a younger.");
        }

        static void sayHi() {
            System.out.println("young is the capital.");
        }
    }

    interface Learner {
        default void print() {
            System.out.println("I am a learner.");
        }
    }

    class Student implements Younger, Learner {
        public void print() {
            Younger.super.print();
            Learner.super.print();
            Younger.sayHi();
            System.out.println("I am a tudent.");
        }
    }

    public static void main(String[] args) {
        Student student = new Student();
        student.print();
    }
}