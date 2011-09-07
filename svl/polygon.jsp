<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib uri="custom" prefix="custom" %>
<%! int n = 256; %> <!-- JSP インスタンスは 1 つだから、static にする
 必要はない -->
<jsp:useBean id="polygon" scope="session" class="com.ayutaya.Polygon" />
<!--
<jsp:setProperty name="polygon" property="radius" param="radius" />
<jsp:setProperty name="polygon" property="numVertex" param="numVertex" />
-->
<jsp:setProperty name="polygon" property="*"/>
<html>
<head><title>polygon result</title></head>
<body>
<h2>多角形の面積（JavaBeansの練習）</h2>
<ul>
  <li>外接円半径: <jsp:getProperty name="polygon" property="radius" />
  <li>頂点の数: <jsp:getProperty name="polygon" property="numVertex" />
  <li>面積: <jsp:getProperty name="polygon" property="area" />
  <li>内角の和: <%= polygon.sumIntAngle() %>
  <li>1 + 2 + 3 + 4 = ${1 + 2 + 3 + 4} # Expression Language
  <li>半径 20 の円の面積: <custom:circle r="20" /> # カスタムタグ
</ul>
</body>
</html>
