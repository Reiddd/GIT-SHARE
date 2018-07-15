import java.sql.*;

public class BatchSupport {
    static final String DB_URL   = "jdbc:mysql://101.132.110.96:3306/JDBC_EXAMPLE?autoReconnect=true&useSSL=false";
    static final String USER     = "root";
    static final String PASSWORD = "Hlw03301227";

    public static void main(String[] args) {
        Connection        conn  = null;
        Statement         stmt  = null;
        PreparedStatement pstmt = null;
        ResultSet         rs    = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            stmt = conn.createStatement();
            conn.setAutoCommit(false);

            String query1 = "INSERT INTO Students(name, age) VALUES('Mike' , 12)";
            String query2 = "INSERT INTO Students(name, age) VALUES('Angle', 13)";
            stmt.addBatch(query1);
            stmt.addBatch(query2);

            int[] res = stmt.executeBatch();
            conn.commit();

        /* +--------------+ */

            conn.setAutoCommit(true);

            String sql = "SELECT * FROM Students WHERE name = ?";
            pstmt      = conn.prepareStatement(sql);

            pstmt.setString(1, "Mike");
            rs = pstmt.executeQuery();
            while (rs.next()) {
                rs.updateInt("age", 14);
                rs.updateRow();
                rs.refreshRow();
                
                System.out.print  ("id: "        + (int)   rs.getInt("id")     );
                System.out.print  (",    name: " + (String)rs.getString("name"));
                System.out.println(",    age: "  + (int)   rs.getInt("age")    );
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            stmt.close();
            pstmt.close();
            conn.close();
        }
    }
}