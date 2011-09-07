import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletResponse;

public class TestFilter implements Filter {
    private ServletContext context = null;
    public void init(FilterConfig config){
        context = config.getServletContext();
    }
    public void destroy() {
        context = null;
    }
    public void doFilter (
      ServletRequest request,
      ServletResponse response,
      FilterChain chain )
      throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = ((HttpServletResponse)response).getWriter();
        Integer count = (Integer)context.getAttribute("count");
        if (count == null) {
            count = new Integer(0);
        }
      int n = count.intValue() + 1;
        context.setAttribute("count",new Integer(n));
        out.println("<b>You have visited " + n +
         " times.</b> (inserted before \"HTML\" tag ...)<p>" );
        chain.doFilter(request,response);
    }
}
