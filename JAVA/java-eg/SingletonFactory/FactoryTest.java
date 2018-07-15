package SingletonFactory;
import SingletonFactory.Products.*;
import SingletonFactory.Factory;

public class FactoryTest {
    public static void main(String[] args) {
        Factory humanFactory = new Factory();
        Human        male         = humanFactory.createHuman("Male");
        Human        female       = humanFactory.createHuman("Female");
        male.eat();
        male.sleep();
        male.work();
        female.eat();
        female.sleep();
        female.work();
    }
}