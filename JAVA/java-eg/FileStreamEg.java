import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class FileStreamEg {
    public static void main(String[] args) {
        try {
            File inFile                = new File("./FileStreamEg_test.txt");
            File outFile               = new File("./FileStreamEg_test1.txt");

            FileInputStream inStream   = new FileInputStream(inFile);
            FileOutputStream outStream = new FileOutputStream(outFile);

            int byte_read;
            while ((byte_read = inStream.read()) != -1) {
                outStream.write(byte_read);
            }

            inStream.close();
            outStream.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}