package AbstractFactory;

public class TableWares {
    public static interface TableWare {
        public String getToolName();
    }

    public static class Knife implements TableWare {
        public String getToolName() {
            return "String";
        }
    }

    public static class Spoon implements TableWare {
        public String getToolName() {
            return "Spoon";
        }
    }
}