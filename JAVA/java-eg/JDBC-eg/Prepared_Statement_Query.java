import java.sql.*;

public class Prepareed_Statement_Query {
    static final String DB_URL   = "jdbc:mysql://101.132.110.96:3306/JDBC_EXAMPLE?autoReconnect=true&useSSL=false";
    static final String USER     = "root";
    static final String PASSWORD = "Hlw03301227";

    public static void main(String[] args) {
        Connection        conn  = null;
        PreparedStatement pstmt = null;

        try {
            // create a connection
            System.out.println("Starting connection...");
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            // build the statement
            System.out.println("Generate the statement...");
            String sql = "UPDATE Students SET age := ? WHERE id = ?";
            pstmt      = conn.preparedStatement(sql);

            // run the query
            System.out.println("querying the database...");
            pstmt.setInt(1, 22);
            pstmt.setInt(2, 1);
            int rows = pstmt.executeUpdate();
            System.out.println("number of rows affected: " + rows);
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            conn.close();
            pstmt.close();
        }
    }
}