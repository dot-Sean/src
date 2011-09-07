package com.ayutaya.struts;

import java.io.IOException;
import org.apache.struts.action.*;

public final class HogeForm extends ActionForm {
  private String name;
  public void setName (
    String name
  ) throws IOException {
      this.name = new String(name.getBytes("8859_1"), "UTF-8");
  }
  public String getName () { return (name); }
};
