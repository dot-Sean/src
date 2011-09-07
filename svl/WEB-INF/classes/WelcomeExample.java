import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WelcomeExample extends HttpServlet {
    public void doGet (
      HttpServletRequest request,
      HttpServletResponse response )
      throws IOException, ServletException {
      PrintWriter out = response.getWriter();
      String title = "Welcome!";
        response.setContentType("text/html");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>" + title + "</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>" + title + "</h1>");
        out.println("</body>");
        out.println("</html>");
    }
}



