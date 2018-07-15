import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileNotFoundException;

public class ReaderEg {
    public static void main(String[] args) {
        try {
            FileInputStream   fis    = new FileinputStream("./DataStreamEg_test.txt");
            InputStreamReader isr    = new InputStreamReader(fis);
            BufferedReader    reader = new BufferedReader(isr);

            String str;
            while ((str = reader.readLine()) != null) {
                System.out.println("Read : " + str);
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException           e) {
            e.printStackTrace();
        } finally {
            isr.close();
        }
    }
}