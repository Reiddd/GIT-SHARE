public class IntegerEg {
    public static void main(String[] args) {
        Integer i1 = new Integer(10);   // initialized from int
        Integer i2 = new Integer(11);
        Integer i3 = new Integer("11"); // initialized from String

        System.out.println("i3 == i2                  : " + (i3 == i2));
        System.out.println("i3.equals(i2)             : " + (i3.equals(i2)));

        i1 = Integer.valueOf(12);           // int
        i1 = Integer.valueOf("010101", 2);  // String + base
        System.out.println("i1.intValue()             : " + i1.intValue());
        System.out.println("i1.toString()             : " + i1.toString());

        int i;
        i = Integer.parseInt("10");
        i = Integer.parseInt("10", 2);
        System.out.println("i                         : " + i);
        System.out.println("Integer.toString(i)       : " + Integer.toString(i));
        System.out.println("Integer.toBinaryString(i) : " + Integer.toBinaryString(i));
    }
}