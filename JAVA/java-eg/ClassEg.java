public class ClassEg {
    public void test() throws ClassNotFoundException {
        String strObj = new String();

        @SuppressWarnings("rawtypes")
        Class classObj;

        classObj = strObj.getClass();
        System.out.println("String object's class is "          + classObj.getName());

        classObj = Integer.class;
        System.out.println("Integer object's class is "         + classObj.getName());

        classObj = Class.forName("java.lang.String");
        System.out.println("Character object's class is "       + classObj.getName());

        classObj = classObj.getSuperclass();
        System.out.println("Character object's super class is " + classObj.getName());
    }

    public static void main(String[] args) {
        try {
            test();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}