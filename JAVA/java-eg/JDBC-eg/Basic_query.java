import java.sql.*;


public class Basic_query {
    // static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL      = "jdbc:mysql://101.132.110.96:3306/JDBC_EXAMPLE?autoReconnect=true&useSSL=false";
    static final String USER        = "root";
    static final String PASSWORD    = "Hlw03301227";

    public static void main(String[] args) {
        Connection conn = null;
        Statement  stmt = null;

        try {
            // register the driver
            // Class.forName("com.mysql.jdbc.Driver");

            // build the connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            // create query statement
            System.out.println("Creating statement...");
            stmt       = conn.createStatement();
            String sql = "SELECT id, name, age FROM Students";

            // run the query
            System.out.println("querying the database...");
            ResultSet rs = stmt.executeQuery(sql);

            while (rs.next()) {
                int    id   = rs.getInt("id");
                int    age  = rs.getInt("age");
                String name = rs.getString("name");

                System.out.print  ("ID: "        + id);
                System.out.print  (",    Age: "  + age);
                System.out.println(",    Name: " + name);
            }
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception    e) {
            e.printStackTrace();
        } finally {
            if (stmt != null) {
                try { stmt.close(); }
                catch (SQLException se1) { se1.printStackTrace(); }
            }
            if (conn != null) {
                try { conn.close(); }
                catch (SQLException se2) { se2.printStackTrace(); }
            }
        }

        System.out.println("GoodBye!");
    }
}
