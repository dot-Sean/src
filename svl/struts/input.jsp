<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="/tags/struts-html" prefix="html" %>
<html:html>
  <head>
    <title>Strutsアプリケーションの基本</title>
  </head>
  <body>
    <h1>Strutsアプリケーションの基本</h1>
    <html:form action="/HogeAction">
      What is your name?<br />
      <html:text property="name" size="20" maxlength="50" />
      <html:submit property="submit" value="表示" />
    </html:form>
  </body>
</html:html>
