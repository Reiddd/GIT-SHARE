package SingletonFactory;

public class Products {
    public static interface Human {
        public void eat();
        public void sleep();
        public void work();
    }

    public static class Male implements Human {
        public void eat() {
            System.out.println("Male can eat.");
        }
        public void sleep() {
            System.out.println("Male can sleep.");
        }
        public void work() {
            System.out.println("Male can work.");
        }
    }

    public static class Female implements Human {
        public void eat() {
            System.out.println("Female can eat.");
        }
        public void sleep() {
            System.out.println("Female can sleep.");
        }
        public void work() {
            System.out.println("Female can work.");
        }
    }
}