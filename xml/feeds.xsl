<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:atom="http://www.w3.org/2005/Atom">
  <xsl:output method="xml" encoding="UTF-8"/>
  <xsl:template match="feeds">
    <feed xmlns="http://www.w3.org/2005/Atom">
      <xsl:for-each select="entry">
        <xsl:for-each select="document(.)/atom:feed/atom:entry">
          <xsl:sort select="atom:author/atom:name/text()"/>
          <xsl:copy-of select="."/>
        </xsl:for-each>
      </xsl:for-each>
    </feed>
  </xsl:template>  
</xsl:stylesheet>
