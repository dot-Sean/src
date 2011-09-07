<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" encoding="UTF-8"
 doctype-public="-//Red Hat, Inc.//DTD Comps info//EN"/>
  <xsl:template match="hoge">
    <html>
      <xsl:apply-templates/>
    </html>
  </xsl:template>
  <xsl:template match="title">
    <head>
      <title>
        <xsl:apply-templates/>
      </title>
    </head>
  </xsl:template>
  <xsl:template match="body">
    <body>
      <h1>
        <!-- <foo><xsl:value-of select="/hoge"/></foo> -->
        <!-- <bar><xsl:copy-of select="/hoge"/></bar> -->
        <xsl:value-of select="/hoge/title"/>
      </h1>
      <p><xsl:apply-templates/></p>
    </body>
  </xsl:template>
</xsl:stylesheet>
