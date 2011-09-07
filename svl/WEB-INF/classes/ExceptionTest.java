import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ExceptionTest extends HttpServlet {
    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    private ServletContext context;
    public void init (ServletConfig config) throws ServletException {
        context = config.getServletContext();
    }
    public void doGet (
      HttpServletRequest request,
      HttpServletResponse response
    ) throws ServletException, IOException {
      String fileData;
        response.setContentType("text/html;charset=UTF-8");
      PrintWriter out = response.getWriter();
        out.println("<html><head><title>ExceptionTest</title></head><body>");
        try {
            if (true) {
                throw new Exception("Yeah!");
            }
          BufferedReader in = 
           new BufferedReader(new FileReader("/sampleData.txt"));
            while((fileData = in.readLine()) != null) {
                out.println(fileData);
            }
            in.close();
        } catch (Exception e) {
            context.log("*** File Read Error in ExceptionTest ***");
            out.println("<p>Error Occured:");
            out.println(e.getMessage());
            out.println("<p><hr><pre>");
            e.printStackTrace(out);
            out.println("</pre>");
        }
        out.println("</body></html>");
        out.close();
    }
}
