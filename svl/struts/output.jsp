<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="/tags/struts-html" prefix="html" %>
<%@ taglib uri="/tags/struts-bean" prefix="bean" %>
<html:html>
  <head>
    <title>Strutsアプリケーションの基本</title>
  </head>
  <body>
    <h1>Strutsアプリケーションの基本</h1>
    Hello, Mr./Ms. <bean:write name="objFrm" property="name" />!
  </body>
</html:html>
