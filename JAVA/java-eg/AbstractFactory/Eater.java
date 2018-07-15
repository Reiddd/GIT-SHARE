package AbstractFactory;
import  AbstractFactory.Kitchens.*;

public class Eater {
    public void eat(Kitchen k) {
        System.out.println("We are eating " + 
                           k.getFood().getFoodName() + 
                           " with " + 
                           k.getTableWare().getToolName());
    }

    public static void main(String[] args) {
        Eater eater = new Eater();
        eater.eat(new Kitchen_A());
        eater.eat(new Kitchen_B());
    }
}