import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class IOStreamEg {
    public static void copy(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[4096];
        int    len    = in.read(buffer);
        while (len != -1) {
            out.write(buffer, 0, len);
            len = in.read(buffer);
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Please enter your input:");
        IOStreamEg.copy(System.in, System.out);
    }
}