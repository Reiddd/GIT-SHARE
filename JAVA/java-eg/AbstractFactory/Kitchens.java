package AbstractFactory;
import  AbstractFactory.Foods.*;
import  AbstractFactory.TableWares.*;

public class Kitchens {
    public static interface Kitchen {
        public Food      getFood();
        public TableWare getTableWare();
    }

    public static class Kitchen_A implements Kitchen {
        static final Food      food      = new Apple();
        static final TableWare tableWare = new Knife();
        public Food getFood() {
            return food;
        }

        public TableWare getTableWare() {
            return tableWare;
        }
    }

    public static class Kitchen_B implements Kitchen {
        static final Food      food      = new Soup();
        static final TableWare tableWare = new Spoon();
        public Food getFood() {
            return food;
        }

        public TableWare getTableWare() {
            return tableWare;
        }
    }
}