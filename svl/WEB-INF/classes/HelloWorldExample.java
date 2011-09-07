import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorldExample extends HttpServlet {
    private String message = null;
    public void init (
      ServletConfig config )
      throws ServletException {
        super.init(config); // Necessary?
        message = getInitParameter("message");
    }
    public void doGet (
      // Java 2 Platform EE 1.3.1: インタフェース HttpServletRequest <http://jp.sun.com/developers/java/docs/j2ee/sdk_1.3/ja/techdocs/api/javax/servlet/http/HttpServletRequest.html>
      HttpServletRequest request,
      HttpServletResponse response )
      throws IOException, ServletException {
//      RequestDispatcher rDispatcher = 
//       request.getRequestDispatcher("/ExceptionTest");
//        rDispatcher.forward(request, response);
      String title = "Hello World!";
      Date now = new Date();
      Cookie cookie = new Cookie("date", now.toString());
        cookie.setMaxAge(60 * 60 * 24 * 7); // 0 to remove
        response.addCookie(cookie);
        //response.addIntHeader("refresh", 5);
        response.setContentType("text/html;charset=UTF-8");
      PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>" + title + "</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>" + title + "</h1>");
        out.println("<p>日本語で表示します。charset の" +
         "指定を先に、writer の取得を後に行なう必要があります。</p>");
        out.println("<p>Remote Addr: " + request.getRemoteAddr() + ", " +
         request.getRemoteHost() );
        out.println("<p>message: " + message);
      ServletContext context = getServletContext();
      String s = (String) context.getAttribute("lastsvl");
        out.println("<p>lastsvl: " + s);
        context.setAttribute("lastsvl", "HelloWorldExample");
      String sDate = null;
      Cookie[] acookie = request.getCookies();
        out.println("<p>Now: " + now.toString());
        if (acookie == null) {
            out.println("<p>No cookie");
        } else {
            for (int i = 0; i < acookie.length; i ++) {
                if (acookie[i].getName().equals("date")) {
                    sDate = acookie[i].getValue();
                    break;
                }
            }
            out.println("<p>Prev: " + sDate);
        }
        out.println("</body>");
        out.println("</html>");
    }
}



