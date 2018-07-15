import java.io.*;
import java.net.*;
import java.lang.Integer;

public class MyTCP {
    private BufferedReader reader;
    private ServerSocket   server;
    private Socket         socket;

    public void getServer() {
        try {
            server = new ServerSocket(8998);
            while (true) {
                System.out.println("Waiting for clients' connection... \n");
                socket         = server.accept();
                InputStream is = socket.getInputStream();
                reader         = new BufferedReader(new InputStreamReader(is));
                System.out.println("Connection established, starting to read... \n");
                getClientMessage();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private void getClientMessage() {
        try {
            Integer count = Integer.valueOf(1);
            System.out.println("Client Message: \n");
            while (true) {
                String msg = reader.readLine();
                System.out.println("Line " + count.intValue() + msg);
                count++;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            if (reader != null) {
                reader.close();
            }
            if (socket != null) {
                socket.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        MyTCP tcp = new MyTCP();
        tcp.getServer();
    }
}