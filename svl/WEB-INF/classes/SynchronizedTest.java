import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SynchronizedTest extends HttpServlet {
    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    public void doGet (
      HttpServletRequest request,
      HttpServletResponse response )
      throws ServletException, IOException {
      String fn = getServletContext().getRealPath("/WEB-INF/counter.txt");
      String strBefore = "";
      String strAfter = "";
      int counter = 0;
      Integer n = null;
      BufferedReader br = null;
      BufferedWriter bw = null;
        response.setContentType("text/html;charset=UTF-8");
      PrintWriter out = response.getWriter();
        out.println("<html><head><title>Sync Test</title></head><body>");
        out.println("<h2> Block Synchronized</h2>");
        try {
            synchronized (this) {
                // カウンターを読む
                br = new BufferedReader(new FileReader(fn));
                strBefore = br.readLine();
                br.close();
                // カウンターを増やす
                counter = Integer.parseInt(strBefore);
                counter ++;
                n = new Integer(counter);
                strAfter = n.toString();
                // カウンターを書き込む
                bw = new BufferedWriter(new FileWriter(fn));
                bw.write(strAfter);
                bw.close();
            }
        } catch (Exception e) {
            out.println("エラー：" + e.getMessage() + "<br><pre>");
            e.printStackTrace(out);
            out.println("</pre>");
        }
        out.println("現在のカウント：" + strBefore+"<p>");
        out.println("更新後のカウント：" + strAfter+"<p>");
      ServletContext context = getServletContext();
      String s = (String) context.getAttribute("lastsvl");
        out.println("<p>lastsvl: " + s);
        context.setAttribute("lastsvl", "SynchronizedTest");
        out.println("</body></html>");
        out.close();
    }
}
