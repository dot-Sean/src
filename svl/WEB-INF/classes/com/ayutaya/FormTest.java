package com.ayutaya;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class FormTest extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost (
      HttpServletRequest request,
      HttpServletResponse response
    ) throws ServletException, IOException {
      // パラメータ取得
      String person = request.getParameter("person");
        // コード変換
        person = new String(person.getBytes("8859_1"), "UTF-8"); 
        // 出力
        response.setContentType("text/html;charset=UTF-8");
      PrintWriter out = response.getWriter();
        out.println("<html><head><title>FormTest</title></head><body>");
        out.println("<p>" + person + "さん、こんにちは。");
        out.println("</body></html>");
        out.close();
    }
}
