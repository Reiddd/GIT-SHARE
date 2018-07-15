package SingletonFactory;
import  SingletonFactory.Products.*;

public class Factory {
    public Human createHuman(String gender) {
        if (gender.equals("Male") || gender.equals("M")) {
            return new Male();
        } 
        else if (gender.equals("Female") || gender.equals("F")) {
            return new Female();
        }
        else {
            System.out.println("Wrong type! ");
            return null;
        }
    }
}