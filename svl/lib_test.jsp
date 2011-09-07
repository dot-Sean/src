<%@ page import="java.util.Date" %>
<html>
<body>
<%
  Date now = new Date();
  Class.forName("org.postgresql.Driver");
%>
<p>d: <%= now.toString() %>
</body>
</html>
