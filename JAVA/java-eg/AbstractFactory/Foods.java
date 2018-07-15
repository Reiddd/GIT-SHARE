package AbstractFactory;

public class Foods {
    public static interface Food {
        public String getFoodName();
    }

    public static class Apple implements Food {
        public String getFoodName() {
            return "Apple";
        }
    }

    public static class Soup implements Food {
        public String getFoodName() {
            return "Soup";
        }
    }
}