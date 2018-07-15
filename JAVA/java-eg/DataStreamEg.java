import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

public class DataStreamEg {
    public static void main(String[] args) {
        try {
        FileOutputStream fos = new FileOutputStream("./DataStreamEg_test.txt");
        DataOutputStream dos = new DataOutputStream(fos);

        dos.writeBoolean(true);
        dos.writeByte((byte)123);
        dos.writeChar('J');
        dos.writeDouble(3.1415926);
        dos.writeFloat(2.122f);
        dos.writeInt(123);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException           e) {
            e.printStackTrace();
        } finally {
            dos.close();
        }

        try {
            FileInputStream fis = new FileInputStream("./DataStreamEg_test.txt");
            DataInputStream dis = new DataInputStream(fis);

            System.out.println("\t" + dis.readBoolean());
            System.out.println("\t" + dis.readByte());
            System.out.println("\t" + dis.readChar());
            System.out.println("\t" + dis.readDouble());
            System.out.println("\t" + dis.readFloat());
            System.out.println("\t" + dis.readInt());
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException           e) {
            e.printStackTrace();
        } finally {
            dis.close();
        }
    }
}