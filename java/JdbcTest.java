import java.lang.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.sql.*;

class JdbcTest {
    static Connection con = null;
    static {
        try {
            //Class.forName("org.postgresql.Driver");
            Class.forName("net.sourceforge.jtds.jdbc.Driver");
            con = DriverManager.getConnection(
             //"jdbc:postgresql://localhost:5432/fuga",
             //"jdbc:postgresql://localhost:5433/task",
             "jdbc:jtds:sybase://192.168.1.2:5000/master",
             "sa",
             "sybase" );
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public static void main (String [] args) {
        System.out.println("JdbcTest!");
        String selQuery = "SELECT * FROM PG_LANGUAGE";
        try {
          DatabaseMetaData meta = con.getMetaData();
          System.out.println("Version: " + meta.getDriverVersion());
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("select * from foo");
            if (rs != null) {
                while (rs.next()) {
                    String val = rs.getString("v");
                    System.out.println("d: " + val);
                }
                rs.close();
            }
            con.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
