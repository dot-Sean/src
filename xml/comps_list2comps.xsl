<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" encoding="UTF-8"
 doctype-public="-//Red Hat, Inc.//DTD Comps info//EN"/>
  <xsl:template match="comps_list">
    <comps>
      <xsl:for-each select="entry">
        <xsl:for-each select="document(.)/comps/group">
          <xsl:copy-of select="."/>
        </xsl:for-each>
      </xsl:for-each>
      <grouphierarchy>
      <xsl:for-each select="entry">
        <xsl:for-each select="document(.)/comps/grouphierarchy/category">
          <xsl:copy-of select="."/>
        </xsl:for-each>
      </xsl:for-each>
      </grouphierarchy>
    </comps>
  </xsl:template>  
</xsl:stylesheet>
